// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Food.h"

Food::~Food(void)
{
}

void Food::update(Uint32 time, Uint32 time_step)
{
	if (_energy <=0)
		destroy();
}

double Food::get_piece(double ant_demand)
{
	double food_consumed = std::min<double>(ant_demand, _energy);
	_energy -= food_consumed;
	_size = calculate_size(_energy);
	if (_energy == 0)
		{ destroy(); }
	return food_consumed;
}

double Food::calculate_size(double energy)
{
	return energy/2.0;
}