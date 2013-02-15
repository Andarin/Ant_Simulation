#include <random>
#ifndef _WIN32
	#include <tr1/random>
#endif
#include <time.h>

void seed(unsigned s);
double unif_01();
