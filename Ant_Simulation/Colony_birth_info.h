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
	int _ant_transport_capability;
	int _ant_olfactory_sense_radius;
	int _ant_life_time;
	int _ant_start_energy;
	int _ant_energy_consumption;
	int _colony_reproduction_speed;
	int _initial_food;
};

