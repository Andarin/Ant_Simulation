#pragma once
#include "Position.h"

class Game_object_birth_info
{
public:
	Game_object_birth_info(void);
	~Game_object_birth_info(void);	

	int _obj_type;
	int _size;
	int _energy;
	int _energy_consumption_per_m;
	Position _pos;
};
