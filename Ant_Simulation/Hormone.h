#pragma once
#include "Game_object.h"
#include "general_constants.h"

class Hormone : public Game_object
{
public:
	Hormone(Game_object_birth_info go_birth_info, int hormone_type):Game_object(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_HORMONE;
		_hormone_type = hormone_type;
	};
	~Hormone(void);

	int _hormone_type;

};