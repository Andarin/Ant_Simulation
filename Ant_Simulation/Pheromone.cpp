#include "Pheromone.h"

Pheromone::~Pheromone(void)
{
}

void Pheromone::merge_pheromone(Pheromone other_phero)
{
	_energy += other_phero._energy;
	other_phero.destroy();
}

void Pheromone::update(void)
{
	_energy = std::min<double>(0, _energy - _energy_consumption);
	_size = 300*_energy/(_energy+1);
	if (_energy == 0)
	{
		destroy();
	}
}