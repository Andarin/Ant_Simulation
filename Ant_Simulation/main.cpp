// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Ant_Sim.h"

int main(int argc, char** argv)
{
	Ant_Sim my_sim;
	//my_sim.start();
	my_sim.start_text_output("sim_example1.sav");
	//my_sim.start_text_input("sim_example2.sav");
	return 0;
}
