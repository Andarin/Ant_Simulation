#pragma once
#include "Game_object.h"

class Pheromone : public Game_object
{
public:
	Pheromone(Game_object_birth_info go_birth_info, int Pheromone_type):Game_object(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_pheromone;
		_pheromone_type = Pheromone_type;
	};
	~Pheromone(void);

	int _pheromone_type;

};