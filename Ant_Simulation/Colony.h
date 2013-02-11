#pragma once
#include "Ant.h"
#include "Colony_birth_info.h"
#include <vector>
#include "general_constants.h"

class Colony
{
public:
	Colony(Colony_birth_info);
	~Colony(void);
	void update(Uint32);
	void enter(Ant);
	void exit(Ant);
	int _color;
	Position _pos;
	int _obj_type;

private:
	double _ant_speed;
	int _ant_attack_points;
	int _ant_armor;
	int _ant_transport_capability;
	int _ant_life_time;
	int _ant_olfactory_sense_radius;
	int _ant_start_energy;
	int _ant_energy_consumption;
	int _egg_production_per_m;
	int _queen_energy_consumption;
	int _queen_hp;
	int _liquid_food;
	int _solid_food;
	int _ant_type_distribution[2];
	std::vector<Ant> ant_vector;
	std::vector<Uint32> larva_vector;
	int _number_of_ants_in_colony;
	int _number_of_larvas_in_colony;

	void transform_food_(void);
	int calc_energy_consumption(int);
	void produce_larvas();
	void test_if_larvas_developped();
};
