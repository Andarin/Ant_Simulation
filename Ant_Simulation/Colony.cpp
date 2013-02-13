#include "Colony.h"

Colony::Colony(Colony_birth_info &Colony_birth_info)
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
	_queen_energy_consumption = calc_energy_consumption(_egg_production_per_m);

	_egg_production_per_m = 60;
	_larva_dev_time = 30; // in s
	_queen_hp = 100;
	_proba_that_ant_is_worker_not_solidier = 1.0;
	_liquid_food = 0;
	_solid_food = 1000;
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

void Colony::produce_larva(Uint32 time)
{
	larva_list.push_back(time + _larva_dev_time);
}

void Colony::test_if_larva_developped(Uint32 time)
{
	if (larva_list.front() < time)
	{
		larva_list.pop_front();
		create_ant(time + _ant_life_time);
	}
}

void Colony::create_ant(Uint32 time)
{
	Ant_birth_info info;
	double rd = unif_01();
	if (rd <= _proba_that_ant_is_worker_not_solidier)
	{ info._ant_type = ANT_TYPE_NR_OF_WORKER; }
	else 
	{ info._ant_type = ANT_TYPE_NR_OF_SOLDIER; }

	info._pos = _pos;
	info._speed = _ant_speed;
	info._attack_points = _ant_attack_points;
	info._armor = _ant_armor;
	info._transport_capability = _ant_transport_capability;
	info._time_of_death = time + _ant_life_time;
	info._color = _color;
	info._olfactory_sense_radius = _ant_olfactory_sense_radius;
	info._energy = 	_ant_start_energy;
	info._energy_consumption = _ant_energy_consumption;

	Ant new_ant(info);
}

int Colony::hand_out_food(int ant_demand)
{
	int take_away_food = 0;
	if (_liquid_food > 0)
		{ take_away_food = min(ant_demand, _liquid_food); }
	return take_away_food;
}

void Colony::store_food(int amount_delivered)
{
	_solid_food += amount_delivered;
}