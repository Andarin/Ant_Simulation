#pragma once
#include "Position.h"

class Ant_birth_info
{
public:
	Ant_birth_info(void);
	~Ant_birth_info(void);	

	Position _pos;
	int _ant_type;
	double _speed;
	int _attack_points;
	int _armor;
	int _transport_capability;
	double _time_of_death;
	int _color;
	int _energy;
	int _energy_consumption_per_m;
};

