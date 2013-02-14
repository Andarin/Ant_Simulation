#include "Food.h"

Food::~Food(void)
{
}

void Food::update(Uint32 time, Uint32 time_step)
{
}

double Food::get_piece(double ant_demand)
{
	double food_consumed = std::min<double>(ant_demand, _energy);
	_energy -= food_consumed;
	if (_energy == 0)
		{ destroy(); }
	return food_consumed;
}