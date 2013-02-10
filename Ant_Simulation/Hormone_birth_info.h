#pragma once
#include "Position.h"

class Hormone_birth_info
{
public:
	Hormone_birth_info(void);
	~Hormone_birth_info(void);	

	Position _pos;
	int _hormone_type;
	double _size;
	int _energy;
	int _energy_consumption;
};
