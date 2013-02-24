// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation

// small file to create a uniform distribution using the
// Mersenne Twister pseudo random generator
// this functionality stems from the Boost library and is included only in
// std:: in C++11; if you use an older version, include the Boost lib
// or delete it and just use the standard uniform distribution
#include <random>
#ifndef _WIN32
	#include <tr1/random>
#endif
#include <time.h>

void seed(unsigned s);
double unif_01();
