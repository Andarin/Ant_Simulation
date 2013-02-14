#include "Food.h"

Food::~Food(void)
{
}

void Food::update(void)
{
}

double Food::get_piece(double ant_demand)
{
	double food_consumed = min(ant_demand, _energy);
	_energy -= food_consumed;
	if (_energy == 0)
		{ destroy(); }
	return food_consumed;
}