#pragma once
#include "Ant_birth_info.h"
#include "Pheromone.h"
#include "Food.h"
#include "general_constants.h"
#include <SDL.h>
#include <vector>

class Ant
{
public:
	Ant(Ant_birth_info&);
	~Ant(void);
	void update(Uint32);
	int _color;
	Position _pos;
	int _obj_type;

private:
	int _ant_type;
	double _speed;
	int _attack_points;
	int _armor;
	int _transport_capability;
	int _size;
	Uint32 _time_of_death;

	double _olfactory_sense_radius;
	int _energy;
	int _energy_consumption;

	void think(void);
	void walk(Position new_position);
	void eat(Game_object food);
	void attack(Game_object target);
	void destroy(void);
	void set_pheromone(void);
	Food transform_food(Food food);
};