// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#pragma once
#include "Position.h"
#ifdef _WIN32
	#include "windows.h"
	#include <SDL.h>
#else
	#include <SDL/SDL.h>
#endif

class Ant_birth_info
{
public:
	Ant_birth_info(void);
	~Ant_birth_info(void);	

	Position _pos;
	int _ant_type;
	double _speed; //as usual speeds, in m.s-1
	int _attack_points;
	int _armor;
	double _transport_capability;
	Uint32 _time_of_death;
	int _color;
	double _energy;
	double _energy_consumption_per_m;
	double _max_distance_before_stop;
	int _ant_status;
};
