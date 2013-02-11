#pragma once
#include "Game_object.h"
#include "general_constants.h"

class Food : public Game_object
{
public:
	Food(Game_object_birth_info go_birth_info, int food_type):Game_object(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_FOOD;
		_hormone_type = food_type;
	};
	~Food(void);

	int _food_type;

};