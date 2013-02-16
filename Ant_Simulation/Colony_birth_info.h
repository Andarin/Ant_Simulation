#pragma once
#include "Position.h"

class Colony_birth_info
{
public:
	Colony_birth_info(void);
	~Colony_birth_info(void);	

	Position _pos;
	int _color;
	double _ant_speed;
	int _ant_attack_points;
	int _ant_armor;
	double _ant_transport_capability;
	int _ant_life_time;
	double _ant_start_energy;
	double _ant_energy_consumption_per_m;
	int _colony_max_reproduction_speed;
	double _initial_food;
};

