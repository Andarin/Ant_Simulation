// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation

// Food is the energy source of the ants. Ants can gather "solid food" from
// food sources via the method "get piece".
#pragma once
#include "Game_item.h"

class Food : public Game_item
{
public:
	Food(Game_item_birth_info go_birth_info):Game_item(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_FOOD;
		_size = calculate_size(_energy);
	};
	~Food(void);
	void update(Uint32, Uint32);
	// API for an ant to demand for food
	double get_piece(double);

private :
	double calculate_size(double energy);
};