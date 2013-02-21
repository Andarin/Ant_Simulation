#include "Ant_Sim.h"

int main(int argc, char** argv)
{
	// user changeable parameters
	int play_time = 600;

	Ant_Sim my_sim(play_time);
	my_sim.start();
	return 0;
}
