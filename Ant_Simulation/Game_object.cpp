#include "Game_object.h"

Game_object::Game_object(Game_object_birth_info go_birth_info) 
{
	_obj_type = -1;
	_size = go_birth_info._size;
	_energy = go_birth_info._energy;
	_energy_consumption = go_birth_info._energy_consumption;
	_pos = go_birth_info._pos;
}

Game_object::~Game_object(void) 
{
}

void Game_object::update(void)
{
	_energy = std::min<int>(0, _energy - _energy_consumption);

	if (_energy == 0)
	{
		destroy();
	}
}

void Game_object::destroy(void)
{
}