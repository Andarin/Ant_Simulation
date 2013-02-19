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
	_pos._direction [0] = 0 ;
	_pos._direction [1] = 1 ;
}

Ant::~Ant(void)
{
}

void Ant::update(Uint32 time, Uint32 time_step,std::list<std::shared_ptr<Ant>> phys_coll_ant,std::list<std::shared_ptr<Colony>> phys_coll_col,std::list<std::shared_ptr<Food>> phys_coll_food)
{
	_energy -= _energy_consumption_per_m*time_step/60000;
	std::list<std::array<double,2>> list_normals = return_normal_board();
	if (_distance_left <= 0 || !list_normals.empty())
	{
		_is_moving = false ;
	}

	if (time > _time_of_death || _energy <= 0)
	{
		destroy();
	}
	else
	{
		_phys_coll_ant = phys_coll_ant;
		_phys_coll_col = phys_coll_col;
		_phys_coll_food = phys_coll_food;

		if (_is_moving)
		{
			_pos._x += (time_step*(_pos._direction[0])*_speed);
			_pos._z += (time_step*(_pos._direction[1])*_speed);
			_distance_left -= time_step*_speed;
		}
		else if (_distance_left <= 0)
		{
			scout_AI (time);
		}
		else if (_time_to_move <= time)
		{
			_is_moving = true;
		}
	}
}

void Ant::update_ph(std::list<std::shared_ptr<Pheromone>> olf_coll_ph)
{
	_olf_coll_ph = olf_coll_ph;
}

//Other behave functions

void Ant::set_pheromone(int phero_type,double energy, double consumption)
{//When an ant set a pheromone it can choose its type, energy and its consumption per minute to some extent
	Game_object_birth_info info;
	info._energy = energy;
	info._energy_consumption_per_m = consumption;
	info._obj_type = OBJECT_TYPE_NR_OF_PHEROMONE;

	std::shared_ptr<Pheromone> p_pheromone = std::make_shared<Pheromone> (info, phero_type);

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
	_distance_left = 50 + 150*unif_01() ;
	double delta = 2*unif_01() -1;
	std::array<double,2> vect = _pos._direction;
	double x = vect[0] - delta*vect[1];
	double z = vect[1] + delta*vect[0];
	double r = sqrt(1 + delta*delta);
	x = x/r;
	z = z/r;
	_pos._direction[0] = x;
	_pos._direction[1] = z;
	Uint32 t = (Uint32) 1000*unif_01();
	_time_to_move = time + t;

}

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
	if (x>= board_size - _size)
	{
		std::array<double,2> vect = {-1,0};
		res.push_back(vect);
	}
	if (z <= _size)
	{
		std::array<double,2> vect = {0,1};
		res.push_back(vect);
	}
	if (z>= board_size - _size)
	{
		std::array<double,2> vect = {0,-1};
		res.push_back(vect);
	}
	return res;
}

std::array<double,2> Ant::find_dir_from_board(std::list<std::array<double,2>> list_norm)
{
	std::array<double,2> res ;
	return res;
}