// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Pheromone.h"

Pheromone::~Pheromone(void)
{
}

double Pheromone::calc_size_by_energy (double energy)
{
	return 300*energy/(energy+1);
}

void Pheromone::merge_pheromone(std::shared_ptr<Pheromone> p_other_phero)
{
	_energy += (*p_other_phero)._energy;
	_pheromone_type = p_other_phero->_pheromone_type;
	_counter = p_other_phero-> _counter;
	(*p_other_phero).destroy();
}

void Pheromone::update(Uint32 time, Uint32 time_step)
{
	_energy = std::max<double>(0, _energy - _energy_consumption_per_m*time_step/60000);
	_size = calc_size_by_energy(_energy);
	if (_energy == 0)
	{
		destroy();
	}
}