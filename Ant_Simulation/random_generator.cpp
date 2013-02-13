#include "random_generator.h"

static std::mt19937 eng (time(NULL));
static std::uniform_real<double> unif(0, 1);

double unif_01()
{
	// to get random number type: double u = unif(eng);
    return unif(eng);
}
