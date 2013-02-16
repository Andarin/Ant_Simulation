#pragma once
#include "Ant_birth_info.h"
#include "Pheromone.h"
#include "Colony.h"
#include "Food.h"
#include "general_constants.h"
#include <list>
#ifdef _WIN32
	#include "windows.h"
	#include <SDL.h>
#else
	#include <SDL/SDL.h>
#endif
#include <vector>

class Colony; // forward declaration because of circle includes

class Ant
{
public:
	Ant(Ant_birth_info&);
	~Ant(void);
	void update(Uint32, Uint32,std::list<std::shared_ptr<Pheromone>>);
	Position _pos;
	int _color;
	int _obj_type;
	bool is_alive(void);

	//A list of the pheromones set by the ant and that have 
	//not been already registered in Table_of_objects
	std::list<std::shared_ptr<Pheromone>> _buffer_fresh_phero ;

private:
	int _ant_type;
	double _speed;
	int _attack_points;
	int _armor;
	double _transport_capability;
	int _size;
	Uint32 _time_of_death;

	double _max_energy_storage;
	double _energy;
	double _energy_consumption_per_m;

	void think(void);
	void walk(Position new_position);
	void restore_energy(Colony col);
	void attack(Game_object target);
	void set_pheromone(int,double,double);
	void destroy(void);
	bool _is_alive;
};
