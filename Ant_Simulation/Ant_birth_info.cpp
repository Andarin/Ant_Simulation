// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Ant_birth_info.h"

Ant_birth_info::Ant_birth_info()
{	
	_ant_type = 0;
	_speed = 0;
	_attack_points = 0;
	_armor = 0;
	_transport_capability = 0;
	_time_of_death = 0;
	_color = 0;
	_max_distance_before_stop = 0;
	_ant_status = 0;
}

Ant_birth_info::~Ant_birth_info(void) 
{
}