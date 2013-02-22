// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation

// Game_item is a general class of items in the simulation and provides
// rudimental functionality. It is the mother class of some other items.
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
	// check if object is still alive; if not it will be deleted by the
	// Table_of_items updater
	bool is_alive(void);

	Position _pos;
	// this variables states the concrete type of the object (e.g. food)
	// only used for testing purposes
	int _obj_type;

	//Get functions
	double get_size (void);
	double get_energy (void);

protected:
	double _size;
	double _energy;
	double _energy_consumption_per_m;
	bool _is_alive;

	void destroy(void);
};