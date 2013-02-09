#pragma once
#include "Ant_birth_info.h"

class Ant
{
public:
	Ant(Ant_birth_info);
	~Ant(void);
	void update();
private:
	const int _ANT_TYPE;
	const double _SPEED;
	const int _ATTACK_POINTS;
	const int _ARMOR;
	const int _TRANSPORT_CAPABILITY;
	const int _COLOR;
	Area Olfactory_area;
	Area corps;
	int _energy;

	void think(void);
	void walk(Pos new_position);
	void eat(Object food);
	void attack(Object target);
	Object transform_food(Object food);
};

