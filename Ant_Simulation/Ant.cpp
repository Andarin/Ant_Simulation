// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Ant.h"

Ant::Ant(Ant_birth_info &ant_birth_info)
{
	_ant_type = ant_birth_info._ant_type;
	_speed = ant_birth_info._speed;
	_attack_points = ant_birth_info._attack_points;
	_armor = ant_birth_info._armor;
	_transport_capability = ant_birth_info._transport_capability;
	_time_of_death = ant_birth_info._time_of_death;
	_color = ant_birth_info._color;
	_max_energy_storage = ant_birth_info._energy;
	_energy = ant_birth_info._energy;
	_energy_consumption_per_m = ant_birth_info._energy_consumption_per_m;
	_size = 10;
	_pos = ant_birth_info._pos;
	_obj_type = OBJECT_TYPE_NR_OF_ANT;
	_is_alive = true;
	_is_moving = false;
	double sq2 = sqrt(2.0);
	_pos._direction [0] = 1/sq2 ;
	_pos._direction [1] = 1/sq2 ;
	_max_distance_before_stop = ant_birth_info._max_distance_before_stop;
	_objective = ant_birth_info._ant_status ;
	_food_stored = 0;
	_time_to_move = 0 ;
	_max_food_storage=1;
	_get_back_colony = false;
	_counter = 0;
}

Ant::~Ant(void)
{
}

void Ant::update(Uint32 time, Uint32 time_step,std::list<std::shared_ptr<Ant>> phys_coll_ant,std::list<std::shared_ptr<Colony>> phys_coll_col,std::list<std::shared_ptr<Food>> phys_coll_food)
{
	_phys_coll_ant = phys_coll_ant;
	_phys_coll_col = phys_coll_col;
	_phys_coll_food = phys_coll_food;

	_energy -= _energy_consumption_per_m*time_step/60000;

	test_should_go_back_because_energy ();

	// if arriving at the border, turn around
	what_should_do_when_meet_board ();
	
	if (time > _time_of_death || _energy <= 0)
	{ destroy(); }
	else
	{
		what_should_do_when_meet_colony();
		what_should_do_when_meet_food();
		
		if (_is_moving)
		{
			//we move the ant according to its past decisions
			//for both direction and distance left
			_pos._x += (time_step*(_pos._direction[0])*_speed);
			_pos._z += (time_step*(_pos._direction[1])*_speed);
			_distance_left -= time_step*_speed;
		}
		else if (_distance_left <= 0)
		{
			AI_chosen_according_to_objective(time);
		}
		else if (_time_to_move <= time)
		{
			_is_moving = true;
		}
	}
	// if temporal target reached, the makes a stop
	if (_distance_left <= 0)
	{ _is_moving = false ; }
}

void Ant::update_ph(std::list<std::shared_ptr<Pheromone>> olf_coll_ph)
{
	_olf_coll_ph = olf_coll_ph;
}

//Other behave functions

void Ant::set_pheromone(int phero_type,double energy, double consumption)
{//When an ant set a pheromone it can choose its type, energy and its consumption per minute to some extent
	Game_item_birth_info info;
	info._energy = energy;
	info._energy_consumption_per_m = consumption;
	info._obj_type = OBJECT_TYPE_NR_OF_PHEROMONE;

	std::shared_ptr<Pheromone> p_pheromone = std::make_shared<Pheromone> (info, phero_type);

	p_pheromone->_counter = _counter;

	_buffer_fresh_phero.push_back(p_pheromone);

}


void Ant::restore_energy(Colony col)//take energy from the colony col
{
	double energy_demand = _max_energy_storage-_energy;
	_energy += col.hand_out_food(energy_demand);
}

void Ant::destroy(void)//the ant is dying
{
	_is_alive = false;
}

//Get/Status functions

bool Ant::is_alive()
{
	return _is_alive ;
}

double Ant::get_size()
{

	return _size ;
}

bool Ant::is_moving()
{
	return _is_moving;
}

//AI functions

void Ant::scout_AI(Uint32 time)
{
	_distance_left = 50 + (_max_distance_before_stop - 50.0)*unif_01() ;
	std::array<double,2> vect = add_unif_noise_45(_pos._direction);
	_pos._direction[0] = vect[0];
	_pos._direction[1] = vect[1];
	Uint32 t = (Uint32) (1000*unif_01());
	_time_to_move = time + t;
	set_pheromone (0,2,1);
}

void Ant::back_AI()
{
	_distance_left = 50 + (_max_distance_before_stop - 50.0)*unif_01() ;
	_pos._direction = direction_phero();
	if (_food_stored > 0)
	{
		set_pheromone (0,10,1);
	}
}

//because of some problem we encountered we create a simpler version of this AI

void Ant::simple_back_AI(Uint32 time)
{
	std::list<std::shared_ptr<Pheromone>> list_back_phero = get_simple_back_phero ();
	if (list_back_phero.empty())
	{
		scout_AI(time);
		if (_food_stored > 0)
			set_pheromone(SIMPLE_AI_PHERO_FOOD,8,1);
		_counter += 1;
	}
	else
	{
		std::list<std::shared_ptr<Pheromone>>::iterator it_possible = list_back_phero.begin();
		int count_min = (*it_possible)->_counter;
		for (std::list<std::shared_ptr<Pheromone>>::iterator it = list_back_phero.begin() ; it != list_back_phero.end() ; ++it)
		{
			int count = (*it)->_counter;
			if (count < count_min)
			{
				count_min = count;
				it_possible = it;
			}
		}
		double x = (*it_possible)->_pos._x - _pos._x ;
		double z = (*it_possible)->_pos._z - _pos._z ;
		double r = sqrt (x*x + z*z);
		x = x/r;
		z = z/r;
		_pos._direction[0] = x;
		_pos._direction[1] = z;
		_distance_left = r+15;
		if (_food_stored > 0)
		{
			set_pheromone(SIMPLE_AI_PHERO_FOOD,10,1);
			_counter += 1;
		}
		Uint32 t = (Uint32) (1000*unif_01());
		_time_to_move = time + t;
	}

}

void Ant::food_AI()
{
	_distance_left = 50 + (_max_distance_before_stop - 50.0)*unif_01() ;
	_pos._direction = direction_phero();
	set_pheromone (0,5,1);
}

void Ant::test_should_go_back_because_energy ()
{
		// if getting hungry, go back to the colony
	if (_energy < 0.5*_max_energy_storage && !_get_back_colony)
	{
		//_pos._direction[0] = -_pos._direction[0];
		//_pos._direction[1] = -_pos._direction[1];
		_objective = ANT_STATUS_BACK_TO_COLONY;
		_get_back_colony = true;
	}
}

void Ant::what_should_do_when_meet_board ()
{
	std::list<std::array<double,2>> list_normals = return_normal_board();
	if (!list_normals.empty())
	{
		board_manager(list_normals);
		_is_moving = true;
	}

}

void Ant::what_should_do_when_meet_colony()
{
	if (!_phys_coll_col.empty())
	{
		_counter = 0;
		//_pos._direction[0] = -_pos._direction[0];
		//_pos._direction[1] = -_pos._direction[1];
		if (_food_stored>0)
		{
			(_phys_coll_col.front())->store_food(_food_stored);
			_food_stored = 0;
			restore_energy (*(_phys_coll_col.front()));
			_get_back_colony = false;
		}

		else if (_energy < 0.5*_max_energy_storage )
		{
			restore_energy (*(_phys_coll_col.front()));
			_get_back_colony = false;
		}

		if (_phys_coll_col.front()->get_if_food_found())
		{
			_objective = ANT_STATUS_GET_FOOD;
		}

		else

		{
			_objective = ANT_STATUS_SCOUT;
		}
	}
}

void Ant::what_should_do_when_meet_food(void)
{
	if (!_phys_coll_food.empty() && _food_stored < _max_food_storage)
	{
		_counter = 0;
		_food_stored += (*(_phys_coll_food.front())).get_piece(_max_food_storage - _food_stored);
		if (_food_stored == _max_food_storage)
		{
		//_pos._direction[0] = -_pos._direction[0];
		//_pos._direction[1] = -_pos._direction[1];
		_objective = ANT_STATUS_BACK_TO_COLONY;
		_get_back_colony = true;
		}
	}
}

void Ant::AI_chosen_according_to_objective (Uint32 time)
{
	if (_objective == ANT_STATUS_SCOUT)
	{
		scout_AI (time);
		set_pheromone(SIMPLE_AI_PHERO_BACK,8,1);
	}
	else if (_objective == ANT_STATUS_BACK_TO_COLONY)
		//back_AI();
		simple_back_AI(time);
	else if (_objective == ANT_STATUS_GET_FOOD)
		//food_AI();
		simple_food_AI(time);
}

//because of some problem we encountered we create a simpler version of this AI

void Ant::simple_food_AI(Uint32 time)
{
	std::list<std::shared_ptr<Pheromone>> list_food_phero = get_simple_food_phero ();
	if (list_food_phero.empty())
	{
		scout_AI(time);
		set_pheromone(SIMPLE_AI_PHERO_BACK,8,1);
		_counter += 1;
	}
	else
	{
		std::list<std::shared_ptr<Pheromone>>::iterator it_possible = list_food_phero.begin();
		int count_min = (*it_possible)->_counter;
		for (std::list<std::shared_ptr<Pheromone>>::iterator it = list_food_phero.begin() ; it != list_food_phero.end() ; ++it)
		{
			int count = (*it)->_counter;
			if (count < count_min)
			{
				count_min = count;
				it_possible = it;
			}
		}
		double x = (*it_possible)->_pos._x - _pos._x ;
		double z = (*it_possible)->_pos._z - _pos._z ;
		double r = sqrt (x*x + z*z);
		x = x/r;
		z = z/r;
		_pos._direction[0] = x;
		_pos._direction[1] = z;
		_distance_left = r - 15;// to prevent from having a merge of two pheromones of diff types we substract 15
		set_pheromone(SIMPLE_AI_PHERO_BACK,10,1);
		_counter += 1;
		Uint32 t = (Uint32) (1000*unif_01());
		_time_to_move = time + t;
	}
}

//Board interaction functions :

std::list<std::array<double,2>> Ant::return_normal_board (void)
{
	std::list<std::array<double,2>> res;
	double x = _pos._x;
	double z = _pos._z;
	if (x <= _size)
	{
		std::array<double,2> vect = {1,0};
		res.push_back(vect);
	}
	if (x>= BOARD_SIZE - _size)
	{
		std::array<double,2> vect = {-1,0};
		res.push_back(vect);
	}
	if (z <= _size)
	{
		std::array<double,2> vect = {0,1};
		res.push_back(vect);
	}
	if (z>= BOARD_SIZE - _size)
	{
		std::array<double,2> vect = {0,-1};
		res.push_back(vect);
	}
	return res;
}

std::array<double,2> Ant::find_dir_from_board(std::list<std::array<double,2>> list_norm)//list_norm is supposed not empty
{
	std::array<double,2> res = {0,0};
	while (!list_norm.empty())
	{
		std::array<double,2> vect = list_norm.back() ;
		res[0] += vect[0];
		res[1] += vect[1];
		list_norm.pop_back();
	}
	double x = res[0];
	double z = res[1];
	double r = sqrt(x*x + z*z);
	res[0] = x/r;
	res[1] = z/r;
	return res;
}

std::array<double,2> Ant::rand_dir_from_board (std::array<double,2> dir)//we suppose dir is a direction (so normalized to 1)
{
	//We first test if we are just on a board and not on a corner
	std::array<double,2> res = {0,0};
	//And we give a determinist deviation of 30° according
	//from where the ant come from...
	if (dir[0] == 0)
	{
		if (_pos._direction[0] <= 0)
		{
			res[0] = -0.5;
			res[1] = dir[1]*(sqrt(3.0)/2);
		}
		else
		{
			res[0] = 0.5;
			res[1] = dir[1]*(sqrt(3.0)/2);
		}
	}
	else if (dir[1] == 0)
	{
		if (_pos._direction[1] <= 0)
		{
			res[1] = -0.5;
			res[0] = dir[1]*(sqrt(3.0)/2);
		}
		else
		{
			res[1] = 0.5;
			res[0] = dir[1]*(sqrt(3.0)/2);
		}
	}
	//else we are in a corner, in this case we don't add a 30° deviation
	else
	{
		res = dir;
	}

	//In all the cases we add a 30° uniform noise

	res = add_unif_noise_30 (res);

	return res;
}

void Ant::board_manager (std::list<std::array<double,2>> list_norm) //the input is the list of normals
{
	_distance_left = 50 + (_max_distance_before_stop - 50.0)*unif_01() ;
	std::array<double,2> dir = find_dir_from_board(list_norm);
	dir = rand_dir_from_board(dir);
	_pos._direction = dir;
}

//Random noise functions

std::array<double,2> Ant::add_unif_noise_45 (std::array<double,2> dir)
{
	std::array<double,2> res;
	double delta = 2*unif_01() -1;
	double x = dir[0] - delta*dir[1];
	double z = dir[1] + delta*dir[0];
	double r = sqrt(1 + delta*delta);
	res[0] = x/r;
	res[1] = z/r;
	return res;
}

std::array<double,2> Ant::add_unif_noise_30 (std::array<double,2> dir)
{
	std::array<double,2> res;
	double delta = unif_01() -0.5;
	double x = dir[0] - delta*dir[1];
	double z = dir[1] + delta*dir[0];
	double r = sqrt(1 + delta*delta);
	res[0] = x/r;
	res[1] = z/r;
	return res;
}

std::array<double,2> Ant::add_triangle_noise_30 (std::array<double,2> dir)
{
	std::array<double,2> res;
	double delta;
	double draw = unif_01();
	if (draw <= 0.5)
	{
		delta = sqrt(draw/2.0) - 0.5;
	}
	else
	{
		delta = 0.5 - sqrt((1-draw)/2.0);
	}
	double x = dir[0] - delta*dir[1];
	double z = dir[1] + delta*dir[0];
	double r = sqrt(1 + delta*delta);
	res[0] = x/r;
	res[1] = z/r;
	return res;
}

//Pheromone observation functions :

void Ant::update_pheros_lists ()
{
	std::list<std::array<double,2>> res_dir ;
	std::list<double> res_nrj ;
	double x_ant = _pos._x;
	double z_ant = _pos._z;
	double x_dir_ant = _pos._direction[0];
	double z_dir_ant = _pos._direction[1];
	for (std::list<std::shared_ptr<Pheromone>>::iterator it = _olf_coll_ph.begin() ; it != _olf_coll_ph.end() ; ++it)
	{
		double x_phero = (*(*it))._pos._x;
		double z_phero = (*(*it))._pos._z;
		double x_dir = x_phero - x_ant ;
		double z_dir = z_phero - z_ant ;
		double r = sqrt (x_dir*x_dir + z_dir*z_dir) ;
		std::array<double,2> vect = {x_dir/r,z_dir/r};
		double energy = (*(*it)).get_energy();
		if (x_dir_ant*vect[0] + z_dir_ant*vect[1] > sqrt(0.5))
		{
			res_dir.push_back(vect);
			res_nrj.push_back(energy);
		}
	}
	_phero_dir = res_dir;
	_phero_energies = res_nrj;
}

int Ant::rank_chosen_phero ()//this list is not empty
{
	int res;
	double total_energy = 0.0 ;
	std::list<double> list_energy = _phero_energies;
	//we calcul first the total energy
	for (std::list<double>::iterator it = list_energy.begin() ; it != list_energy.end() ; ++it)
	{
		total_energy += *it ;
	}

	//now we choose randomly the pheromone depending on its energy

	double draw = unif_01()*total_energy;
	double cumulate_energy = 0.0 ;
	int incr = 0 ;

	for (std::list<double>::iterator it = list_energy.begin() ; it != list_energy.end() ; ++it)
	{
		if (draw >= cumulate_energy && draw <= (cumulate_energy +*it))
		{
			res = incr;
		}
		cumulate_energy += *it ;
		incr += 1 ;
	}

	return res ;
}

std::array<double,2> Ant::direction_phero (void)
{
	update_pheros_lists();
	std::array<double,2> res;
	if (!_phero_dir.empty())
	{
		std::list<std::array<double,2>>::iterator it = _phero_dir.begin();
		int N = rank_chosen_phero ();
		std::advance(it,N);
		res = *it;
	}
	else 
	{
		double draw = unif_01();
		if (draw <= 0.5)
		{
			res[0] = -_pos._direction[1];
			res[1] = _pos._direction[0];
		}
		else
		{
			res[0] = _pos._direction[1];
			res[1] = -_pos._direction[0];
		}
	}

	res = add_triangle_noise_30 (res);
	return res;
}

std::list<std::shared_ptr<Pheromone>> Ant::get_simple_back_phero ()
{
	std::list<std::shared_ptr<Pheromone>> res ;
	for (std::list<std::shared_ptr<Pheromone>>::iterator it = _olf_coll_ph.begin() ; it != _olf_coll_ph.end() ; ++it)
	{
		if ( (*it)->_pheromone_type == SIMPLE_AI_PHERO_BACK)
			res.push_back( (*it));
	}
	return res;
}

std::list<std::shared_ptr<Pheromone>> Ant::get_simple_food_phero ()
{
	std::list<std::shared_ptr<Pheromone>> res ;
	for (std::list<std::shared_ptr<Pheromone>>::iterator it = _olf_coll_ph.begin() ; it != _olf_coll_ph.end() ; ++it)
	{
		if ( (*it)->_pheromone_type == SIMPLE_AI_PHERO_FOOD)
			res.push_back( (*it));
	}
	return res;
}