#pragma once
#include "Game_object_birth_info.h"
#include "models.h"
#include "Position.h"
#include "general_constants.h"

class Game_object
{
public:
	Game_object(Game_object_birth_info go_birth_info);
	~Game_object(void);
	void update(void);
	Position _pos;
	int _obj_type;

protected:
	int _pheromone_type;
	int _size;
	int _energy;
	int _energy_consumption;

	void destroy(void);
};