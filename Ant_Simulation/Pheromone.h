#pragma once
#include "Game_object.h"
#include "general_constants.h"

class Pheromone : public Game_object
{
public:
	Pheromone(Game_object_birth_info go_birth_info, int pheromone_type):Game_object(go_birth_info)
	{
		_obj_type = OBJECT_TYPE_NR_OF_PHEROMONE;
		_pheromone_type = pheromone_type;
	};
	~Pheromone(void);

	int _pheromone_type;
};