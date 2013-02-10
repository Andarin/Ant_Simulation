#pragma once
#include "Hormone_birth_info.h"
#include "Position.h"
#include <algorithm>

class Hormone
{
public:
	Hormone(Hormone_birth_info);
	~Hormone(void);
	void update();
	Position _pos;
	int _obj_type;

private:
	int _hormone_type;
	int _size;
	int _energy;
	int _energy_consumption;
	void destroy(void);
};