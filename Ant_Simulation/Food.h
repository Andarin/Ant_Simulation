#pragma once
#include "Game_object.h"

class Food : public Game_object
{
public:
	Food(Game_object_birth_info go_birth_info, int food_type):Game_object(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_FOOD;
		_food_type = food_type;
	};
	~Food(void);
	void update(void);
	double get_piece(double);

	int _food_type;
};