#pragma once
#include "Ant.h"
#include <vector>

class Colony
{
public:
	Colony(Colony_birth_info);
	~Colony(void);
	void update();
	void enter(Ant);
	void exit(Ant);
private:
	const int _COLOR;
	const double _ANT_SPEED;
	const int _ANT_ATTACK_POINTS;
	const int _ANT_ARMOR;
	const int _ANT_TRANSPORT_CAPABILITY;
	Area corps;
	int _ant_type_distribution[2];
	std::vector<Ant> ant_vector;

	void transform_food_(void);
	void produce_new_workers();
};
