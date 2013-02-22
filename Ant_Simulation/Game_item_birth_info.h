// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#pragma once
#include "Position.h"

class Game_item_birth_info
{
public:
	Game_item_birth_info(void);
	~Game_item_birth_info(void);

	int _obj_type;
	double _size;
	double _energy;
	double _energy_consumption_per_m;
	Position _pos;
};
