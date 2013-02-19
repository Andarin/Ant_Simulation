#pragma once

#include <list>
#include <memory>

#include "Ant.h"
#include "Colony_birth_info.h"
#include "general_constants.h"
#include "random_generator.h"

class Ant; // forward declaration because of circle include

class Colony
{
public:
	Colony(Colony_birth_info&);
	~Colony(void);
	void update(Uint32, Uint32);
	int _obj_type;
	Position _pos;
	double hand_out_food(double);
	void store_food(double);
	void change_egg_production(int);
	bool is_alive(void);

	//A list of the ant that have been recently created
	//Their positions will be define in table_of_objects
	std::list<std::shared_ptr<Ant>> _buffer_fresh_ant;

	double get_size (void);
	double get_liquid_food(void);
	double get_solid_food(void);
	int get_queen_hp(void);
	int get_number_of_larvas(void);

private:
	int _color;
	double _ant_speed; // in m/s
	int _ant_attack_points;
	int _ant_armor;
	double _ant_transport_capability;
	int _ant_life_time; // in s
	double _ant_start_energy;
	double _ant_energy_consumption_per_m;
	// a list with times when larvas will develop to ants
	std::list<Uint32> _larva_list;

	// set inside the class
	int _egg_production_per_m;
	int _max_egg_production_per_m;
	double _every_XX_ms_egg;
	Uint32 _egg_time_accumulated;
	int _larva_dev_time;
	int _queen_hp;
	double _proba_that_ant_is_worker_not_solidier;
	double _liquid_food;
	double _solid_food;
	bool _is_alive;
	double _size;

	void transform_food(Uint32);
	void check_if_queen_starves(void);
	void calc_energy_consumption(Uint32);
	void lay_egg(Uint32, Uint32);
	void produce_larva(Uint32);
	void test_if_larva_developped(Uint32);
	void create_ant(Uint32);
	void destroy(void);
};
