#pragma once
#include "Ant.h"
#include "Colony_birth_info.h"
#include <list>
#include "general_constants.h"
#include "random_generator.h"

class Colony
{
public:
	Colony(Colony_birth_info&);
	~Colony(void);
	void update(Uint32);
	void enter(Ant);
	void exit(Ant);
	int _obj_type;

	std::list<std::shared_ptr<Ant> > _ant_list;

private:
	int _color;
	Position _pos;
	double _ant_speed;
	int _ant_attack_points;
	int _ant_armor;
	int _ant_transport_capability;
	int _ant_life_time;
	int _ant_olfactory_sense_radius;
	int _ant_start_energy;
	int _ant_energy_consumption;
	int _queen_energy_consumption;
	// a list with times when larvas will devellop to ants
	std::list<Uint32> larva_list;

	// set inside the class
	int _egg_production_per_m;
	int _larva_dev_time;
	int _queen_hp;
	double _proba_that_ant_is_worker_not_solidier;
	int _liquid_food;
	int _solid_food;

	void transform_food_(void);
	int calc_energy_consumption(int);
	void produce_larva(Uint32);
	void test_if_larva_developped(Uint32);
	void create_ant(Uint32);
	int hand_out_food(int);
	void store_food(int);
};
