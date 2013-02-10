#include "Game_object.h"

Game_object::Game_object() 
{
}

Game_object::Game_object(Game_object_birth_info go_birth_info) 
{
	_obj_type = -1;
	_pos = go_birth_info._pos;
}

Game_object::~Game_object(void) 
{
}