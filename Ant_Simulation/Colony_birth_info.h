// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Position.h"

class Colony_birth_info
{
public:
	Colony_birth_info(void);
	~Colony_birth_info(void);
	void read_from_file(std::string);

	Position _pos;
	int _color;
	double _ant_speed; // in m/s
	int _ant_attack_points;
	int _ant_armor;
	double _ant_transport_capability;
	int _ant_life_time; // in s
	double _ant_start_energy;
	double _ant_energy_consumption_per_m;
	double _ant_max_distance_before_stop;
	int _colony_max_reproduction_speed;
	double _initial_food;
	double _larva_dev_time;
	double _size;
};

