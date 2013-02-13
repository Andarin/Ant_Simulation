#include "Ant.h"

Ant::Ant(Ant_birth_info ant_birth_info)
{
	_ant_type = ant_birth_info._ant_type;
	_speed = ant_birth_info._speed;
	_attack_points = ant_birth_info._attack_points;
	_armor = ant_birth_info._armor;
	_transport_capability = ant_birth_info._transport_capability;
	_time_of_death = ant_birth_info._time_of_death;
	_color = ant_birth_info._color;
	_olfactory_sense_radius = ant_birth_info._olfactory_sense_radius;
	_energy = ant_birth_info._energy;
	_energy_consumption = ant_birth_info._energy_consumption;;
	_size = 1;
	_pos = ant_birth_info._pos;
	_obj_type = OBJECT_TYPE_NR_OF_ANT;
}

Ant::~Ant(void)
{
}

void Ant::update(Uint32 time)
{
	_energy -= _energy_consumption;

	if (time > _time_of_death || _energy <= 0)
	{
		destroy();
	}


}

void Ant::destroy(void)
{
}

void Ant::set_pheromone(void)
{
}