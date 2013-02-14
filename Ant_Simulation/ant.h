#pragma once
#include "Ant_birth_info.h"
#include "Pheromone.h"
#include "Colony.h"
#include "Food.h"
#include "general_constants.h"
#include <SDL.h>
#include <vector>

class Colony;

class Ant
{
public:
	Ant(Ant_birth_info&);
	~Ant(void);
	void update(Uint32);
	std::shared_ptr<Position> get_position(void);

	int _color;
	int _obj_type;

private:
	std::shared_ptr<Position> _pos_ptr;
	int _ant_type;
	double _speed;
	int _attack_points;
	int _armor;
	double _transport_capability;
	int _size;
	Uint32 _time_of_death;

	double _olfactory_sense_radius;
	double _max_energy_storage;
	double _energy;
	double _energy_consumption;

	void think(void);
	void walk(Position new_position);
	void restore_energy(Colony col);
	void attack(Game_object target);
	void set_pheromone(int);
	void destroy(void);
};