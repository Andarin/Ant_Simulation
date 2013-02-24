// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#pragma once
#include "Game_item.h"

// obstacles in the game environment to make the life of the ants more
// difficult and to create different maps
// until now they can be displayed but there is not yet collision detection
class Obstacle : public Game_item
{
public:
	Obstacle(Game_item_birth_info go_birth_info):Game_item(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_OBSTACLE;
	};
	~Obstacle(void);
};