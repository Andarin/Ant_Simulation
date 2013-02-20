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
	std::vector<std::string> lines;
	std::ifstream fin(file_name);
	std::string line;
	while( std::getline(fin, line) )
	{
		lines.push_back(line);
	}
	double reproduction_speed = atof(lines[19].c_str());
	std::cout << reproduction_speed+3 << std::endl;
}