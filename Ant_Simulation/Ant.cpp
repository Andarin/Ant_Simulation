#include "ant.h"

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
	_size = 1;
	_pos = ant_birth_info._pos;
	_obj_type = OBJECT_TYPE_NR_OF_ANT;
}

Ant::~Ant(void)
{
}

void Ant::update(Uint32 time, Uint32 time_step,std::list<std::shared_ptr<Pheromone>> list_ph_coll)
{
	_energy -= _energy_consumption_per_m*time_step/60000;

	if (time > _time_of_death || _energy <= 0)
	{
		destroy();
	}
}

void Ant::set_pheromone(int phero_type)
{
	Game_object_birth_info info;
	info._pos = _pos;
	info._energy = 100;
	info._energy_consumption_per_m = 1;
	info._size = 400;
	info._obj_type = OBJECT_TYPE_NR_OF_PHEROMONE;

	// where to put it
	// ???????????
	Pheromone new_phero(info, phero_type); 
}

void Ant::restore_energy(Colony col)
{
	double energy_demand = _max_energy_storage-_energy;
	_energy += col.hand_out_food(energy_demand);
}

void Ant::destroy(void)
{
}
