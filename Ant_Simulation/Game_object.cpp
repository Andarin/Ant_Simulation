#include "Game_object.h"

Game_object::Game_object(Game_object_birth_info go_birth_info) 
{
	_obj_type = -1;
	_size = go_birth_info._size;
	_energy = go_birth_info._energy;
	_energy_consumption_per_m = go_birth_info._energy_consumption_per_m;

	_pos = go_birth_info._pos;
}

Game_object::~Game_object(void) 
{
}

void Game_object::destroy(void)
{
}