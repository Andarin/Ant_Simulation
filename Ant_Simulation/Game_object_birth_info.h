#pragma once
#include "Position.h"

class Game_object_birth_info
{
public:
	Game_object_birth_info(void);
	~Game_object_birth_info(void);	

	int _obj_type;
	double _size;
	double _energy;
	double _energy_consumption_per_m;
	Position _pos;
};
