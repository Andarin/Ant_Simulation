#pragma once
#include <memory>

#include "Game_object_birth_info.h"
#include "models.h"
#include "Position.h"
#include "general_constants.h"

class Game_object
{
public:
	Game_object(Game_object_birth_info go_birth_info);
	~Game_object(void);
	bool is_alive(void);

	Position _pos;
	int _obj_type;

	//Get functions
	double get_size (void);

protected:
	int _pheromone_type;
	double _size;
	double _energy;
	double _energy_consumption_per_m;
	bool _is_alive;

	void destroy(void);
};