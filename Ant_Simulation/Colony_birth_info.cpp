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
	_ant_speed = atof(lines[42].c_str());
	_ant_attack_points = atof(lines[54].c_str());
	_ant_armor = atof(lines[56].c_str());
	_ant_transport_capability = atof(lines[52].c_str());
	_ant_life_time = atof(lines[44].c_str());
	_ant_start_energy = atof(lines[46].c_str());
	_ant_energy_consumption_per_m = atof(lines[48].c_str());
	_ant_max_distance_before_stop = atof(lines[50].c_str());
	_colony_max_reproduction_speed = atof(lines[38].c_str());
	_initial_food = atof(lines[40].c_str());

	// Set colony position
	double colony_x = atof(lines[32].c_str());
	double colony_z = atof(lines[34].c_str());
	std::array<double, 2> dir = {1.0, 0.0};
	Position pos(colony_x,1,colony_z,dir);
	_pos = pos;
}