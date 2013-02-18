#pragma once
#include "Ant_birth_info.h"
#include "Pheromone.h"
#include "Colony.h"
#include "Food.h"
#include "general_constants.h"
#include <list>
#include <vector>

class Colony; // forward declaration because of circle includes

class Ant
{
public:
	Ant(Ant_birth_info&);
	~Ant(void);
	//Update functions :
	 //This function, called in the collision detector, update some ant's variable
	 //(such as position...) and its lists of physical collisions.
	void update(Uint32, Uint32,std::list<std::shared_ptr<Ant>>,
		std::list<std::shared_ptr<Colony>>,std::list<std::shared_ptr<Food>>);

	//Update of the collisions with pheromones, called when the ant stops
	void update_ph (std::list<std::shared_ptr<Pheromone>>);

	//Public variables :
	Position _pos;
	int _color;
	int _obj_type;

	//A list of the pheromones set by the ant and that have 
	//not been already registered in Table_of_objects
	std::list<std::shared_ptr<Pheromone>> _buffer_fresh_phero ;

	//Get functions :
	double get_size (void);
	bool is_moving (void);
	bool is_alive(void);

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
	bool _is_moving;

	//list of olfactive collisions of the ant with pheromones

	std::list<std::shared_ptr<Pheromone>> _olf_coll_ph ;

	//lists of the objects in physical collisions with the ant

	std::list<std::shared_ptr<Ant>> _phys_coll_ant ;//collision with other ants
	std::list<std::shared_ptr<Colony>> _phys_coll_col ;//collision with colonies
	std::list<std::shared_ptr<Food>> _phys_coll_food ;//collision with food

};
