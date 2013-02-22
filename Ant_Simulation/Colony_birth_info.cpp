// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Colony_birth_info.h"

Colony_birth_info::Colony_birth_info(void) 
{
	_color = 0;
	_ant_speed = 0; // in m/s
	_ant_attack_points = 0;
	_ant_armor = 0;
	_ant_transport_capability = 0;
	_ant_life_time = 0; // in s
	_ant_start_energy = 0;
	_ant_energy_consumption_per_m = 0;
	_ant_max_distance_before_stop = 0;
	_colony_max_reproduction_speed = 0;
	_initial_food = 0;
	_larva_dev_time = 0;
	_size = 0;
}

Colony_birth_info::~Colony_birth_info(void) 
{
}

void Colony_birth_info::read_from_file(std::string file_name)
{
	// read in file in vector of strings
	std::vector<std::string> lines;
	std::ifstream fin(file_name);
	std::string line;
	while( std::getline(fin, line) )
	{
		lines.push_back(line);
	}

	// transform lines into numbers and pass them to the variables
	_ant_speed = atof(lines[30].c_str());
	_ant_attack_points = atof(lines[47].c_str());
	_ant_armor = atof(lines[49].c_str());
	_ant_transport_capability = atof(lines[45].c_str());
	_ant_life_time = atof(lines[37].c_str());
	_ant_start_energy = atof(lines[39].c_str());
	_ant_energy_consumption_per_m = atof(lines[41].c_str());
	_ant_max_distance_before_stop = atof(lines[43].c_str());
	_colony_max_reproduction_speed = atof(lines[26].c_str());
	_initial_food = atof(lines[28].c_str());
	_larva_dev_time = atof(lines[35].c_str());

	// Set colony position
	double colony_x = atof(lines[20].c_str());
	double colony_z = atof(lines[22].c_str());
	std::array<double, 2> dir = {1.0, 0.0};
	Position pos(colony_x,1,colony_z,dir);
	_pos = pos;
}