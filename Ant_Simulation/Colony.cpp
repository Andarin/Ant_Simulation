// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Colony.h"

Colony::Colony(Colony_birth_info &colony_birth_info)
{
	// variables set by the given birth information
	_pos = colony_birth_info._pos;
	_color = colony_birth_info._color;
	_ant_speed = colony_birth_info._ant_speed;
	_ant_attack_points = colony_birth_info._ant_attack_points;
	_ant_armor = colony_birth_info._ant_armor;
	_ant_transport_capability = colony_birth_info._ant_transport_capability;
	_ant_life_time = colony_birth_info._ant_life_time;
	_ant_start_energy = colony_birth_info._ant_start_energy;
	_ant_energy_consumption_per_m = colony_birth_info._ant_energy_consumption_per_m;
	_ant_max_distance_before_stop = colony_birth_info._ant_max_distance_before_stop;
	_max_egg_production_per_m = colony_birth_info._colony_max_reproduction_speed;
	_liquid_food = colony_birth_info._initial_food;
	_larva_dev_time = colony_birth_info._larva_dev_time; // in s
	_size = colony_birth_info._size;

	// variables set inside the colony
	_obj_type = OBJECT_TYPE_NR_OF_COLONY;
	_food_found = false;
	_food_found_timer = 0;
	_egg_production_per_m = _max_egg_production_per_m;
	_every_XX_ms_egg = 60000.0/_egg_production_per_m;
	_egg_time_accumulated = _every_XX_ms_egg; // in ms
	_queen_hp = 100;
	_proba_that_ant_is_solidier = 0.0;
	_solid_food = 0.0;
	_is_alive = true;
}

Colony::~Colony(void)
{
}

void Colony::update(Uint32 time, Uint32 time_step)
{
	check_if_queen_starves(time_step);
	if (_queen_hp <= 0) 
	{
		destroy();
	}
	else {
		calc_energy_consumption(time_step);
		update_alarm_status(time_step);
		lay_egg(time, time_step);
		test_if_larva_developped(time);
		transform_food(time_step);
	}
}

void Colony::calc_energy_consumption(Uint32 time_step)
{
	// energy consumption is linear to egg production
	_liquid_food = std::max<double>(_liquid_food-time_step/_every_XX_ms_egg, 0);
}

void Colony::update_alarm_status(Uint32 time_step)
{
	_food_found_timer = std::max<Uint32>(_food_found_timer-time_step,0);
	if (_food_found_timer <= 0)
		_food_found = false;
}

void Colony::check_if_queen_starves(Uint32 time_step)
{
	// Queen looses health if there is no food
	if (_liquid_food == 0)
		{ _queen_hp -= time_step/600; }
}

void Colony::lay_egg(Uint32 time, Uint32 time_step)
{
	_egg_time_accumulated += time_step;
	while (_egg_time_accumulated >= _every_XX_ms_egg)
	{
		_egg_time_accumulated -= _every_XX_ms_egg;
		produce_larva(time);
	}
}

void Colony::produce_larva(Uint32 time)
{
	_larva_list.push_back(time + _larva_dev_time*1000);
}

void Colony::test_if_larva_developped(Uint32 time)
{
	if (!_larva_list.empty() && _larva_list.front() < time)
	{
		_larva_list.pop_front();
		create_ant(time + _ant_life_time);
	}
}

void Colony::transform_food(Uint32 time_step)
{
	// one larva transforms one unity of solid food per sec to liquid food
	double food_transformed = std::min<double>(_larva_list.size()*time_step/10000.0,_solid_food);
	_solid_food -= food_transformed;
	_liquid_food += food_transformed;
}

void Colony::create_ant(Uint32 time)
{
	Ant_birth_info info;
	double rd = unif_01();
	if (rd <= _proba_that_ant_is_solidier)
	{ info._ant_type = ANT_TYPE_NR_OF_SOLDIER; }
	else 
	{ info._ant_type = ANT_TYPE_NR_OF_WORKER; }
	info._speed = _ant_speed;
	info._attack_points = _ant_attack_points;
	info._armor = _ant_armor;
	info._transport_capability = _ant_transport_capability;
	info._time_of_death = time + _ant_life_time*1000;
	info._color = _color;
	info._energy = _ant_start_energy;
	info._energy_consumption_per_m = _ant_energy_consumption_per_m;
	info._max_distance_before_stop = _ant_max_distance_before_stop;
	if (_food_found)
		info._ant_status = ANT_STATUS_GET_FOOD;
	else
		info._ant_status = ANT_STATUS_SCOUT;
	std::shared_ptr<Ant> p_ant = std::make_shared<Ant> (info);
	_buffer_fresh_ant.push_back(p_ant);
}

double Colony::hand_out_food(double ant_demand)
{
	double take_away_food = 0;
	if (_liquid_food > 0)
		{ take_away_food = std::min<double>(ant_demand, _liquid_food); }
	return take_away_food;
}

void Colony::store_food(double amount_delivered)
{
	_solid_food += amount_delivered;
	_food_found = true;
	_food_found_timer = 30000;
}

void Colony::change_egg_production(int new_egg_production)
{
	_egg_production_per_m = std::min<int>(new_egg_production, _max_egg_production_per_m);
	_every_XX_ms_egg = 60000/_egg_production_per_m;
}

bool Colony::is_alive(void)
{
	return _is_alive;
}

void Colony::destroy(void)
{
	_is_alive = false;
}

double Colony::get_size()
{
	return _size;
}

double Colony::get_liquid_food()
{
	return _liquid_food;
}

double Colony::get_solid_food()
{
	return _solid_food;
}

int Colony::get_queen_hp()
{
	return _queen_hp;
}

int Colony::get_number_of_larvas()
{
	return _larva_list.size();
}

bool Colony::get_if_food_found()
{
	return _food_found ;
}