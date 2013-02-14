#include "Pheromone.h"

Pheromone::~Pheromone(void)
{
}

void Pheromone::merge_pheromone(Pheromone other_phero)
{
	_energy += other_phero._energy;
	other_phero.destroy();
}