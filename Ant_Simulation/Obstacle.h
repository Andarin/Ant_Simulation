#pragma once
#include "Game_item.h"

class Obstacle : public Game_item
{
public:
	Obstacle(Game_item_birth_info go_birth_info):Game_item(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_OBSTACLE;
	};
	~Obstacle(void);
};