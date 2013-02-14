#include "Pheromone.h"

Pheromone::~Pheromone(void)
{
}

void Pheromone::merge_pheromone(Pheromone other_phero)
{
	_energy += other_phero._energy;
	other_phero.destroy();
}

void Pheromone::update(Uint32 time, Uint32 time_step)
{
	_energy = std::min<double>(0, _energy - _energy_consumption_per_m*time_step/60000);
	_size = 300*_energy/(_energy+1);
	if (_energy == 0)
	{
		destroy();
	}
}