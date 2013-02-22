// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation

// class of pheromones; they are created by ants and food and are used by the
// blind ants to get an image of their environment
#pragma once
#include "Game_item.h"
#include "general_constants.h"

class Pheromone : public Game_item
{
public:
	Pheromone(Game_item_birth_info go_birth_info, int pheromone_type):Game_item(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_PHEROMONE;
		_pheromone_type = pheromone_type;
		_size = calc_size_by_energy(_energy);
	};
	~Pheromone(void);
	void update(Uint32, Uint32);

	// if two pheromones are very close, merge them to save calculations
	void merge_pheromone(std::shared_ptr<Pheromone>);

	//give the size of pheromone accordingly to its energy
	double calc_size_by_energy (double);
	
	// variables
	int _pheromone_type;
	int _counter;
};