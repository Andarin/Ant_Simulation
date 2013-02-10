#include "Colony.h"

Colony::Colony(Colony_birth_info Colony_birth_info)
{
	_ant_speed = Colony_birth_info._ant_speed;
	_ant_attack_points = Colony_birth_info._ant_attack_points;
	_ant_armor = Colony_birth_info._ant_armor;
	_ant_transport_capability = Colony_birth_info._ant_transport_capability;
	_ant_life_time = Colony_birth_info._ant_life_time;
	_color = Colony_birth_info._color;
	_ant_olfactory_sense_radius = Colony_birth_info._ant_olfactory_sense_radius;
	_ant_start_energy = Colony_birth_info._ant_start_energy;
	_ant_energy_consumption = Colony_birth_info._ant_energy_consumption;
	_pos = Colony_birth_info._pos;
	_obj_type = OBJECT_TYPE_NR_OF_COLONY;
	_egg_production_per_m = 60;
	_queen_energy_consumption = calc_energy_consumption(_egg_production_per_m);

	_queen_hp = 100;
}

Colony::~Colony(void)
{
}

void Colony::update(Uint32 time)
{
}

int Colony::calc_energy_consumption(int eggs_per_minute)
{
	return eggs_per_minute;
}