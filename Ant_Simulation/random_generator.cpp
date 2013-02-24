// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "random_generator.h"

static std::mt19937 eng (time(NULL));
static std::uniform_real_distribution<double> unif(0, 1);

double unif_01()
{
	// to get random number type: double u = unif(eng);
    return unif(eng);
}
