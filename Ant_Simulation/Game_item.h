#pragma once
#include <memory>

#include "Game_item_birth_info.h"
#include "models.h"
#include "Position.h"
#include "general_constants.h"

class Game_item
{
public:
	Game_item(Game_item_birth_info go_birth_info);
	~Game_item(void);
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