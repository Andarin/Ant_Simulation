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
	if (_distance_left <= 0)
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
			_pos._x += (time_step/1000*(_pos._direction[0])*_speed);
			_pos._y += (time_step/1000*(_pos._direction[1])*_speed);
			_distance_left -= time_step/1000*_speed;
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


}