#include "Game_item.h"

Game_item::Game_item(Game_item_birth_info go_birth_info) 
{
	_obj_type = go_birth_info._obj_type;
	_energy = go_birth_info._energy;
	_size = go_birth_info._size;
	_energy_consumption_per_m = go_birth_info._energy_consumption_per_m;

	_pos = go_birth_info._pos;
	_is_alive = true;
}

Game_item::~Game_item(void) 
{
}

bool Game_item::is_alive(void)
{
	return _is_alive;
}

void Game_item::destroy(void)
{
	_is_alive = false;
}

double Game_item::get_size(void)
{
	return _size;
}