// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#pragma once
// external libs
#include <list>
#include <memory>
// self created libs
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
	//Their positions will be define in table_of_items
	std::list<std::shared_ptr<Ant>> _buffer_fresh_ant;

	double get_size (void);
	double get_liquid_food(void);
	double get_solid_food(void);
	int get_queen_hp(void);
	int get_number_of_larvas(void);
	int _color;
	bool get_if_food_found(void);

private:
	double _ant_speed; // in m/s
	int _ant_attack_points;
	int _ant_armor;
	double _ant_transport_capability;
	int _ant_life_time; // in s
	double _ant_start_energy;
	double _ant_energy_consumption_per_m;
	double _ant_max_distance_before_stop;
	// a list with times when larvas will develop to ants
	std::list<Uint32> _larva_list;

	// set inside the class
	int _egg_production_per_m;
	int _max_egg_production_per_m;
	double _every_XX_ms_egg;
	Uint32 _egg_time_accumulated;
	int _larva_dev_time;
	int _queen_hp;
	double _proba_that_ant_is_solidier;
	double _liquid_food;
	double _solid_food;
	bool _is_alive;
	// alarm colony if an ant returned with food
	// hence all the spawning ants will follow the path to the food
	bool _food_found;
	// stop time since last food found in order to return to
	// scout-mode when food source is exhausted
	Uint32 _food_found_timer; // in ms
	double _size;

	void transform_food(Uint32);
	void check_if_queen_starves(Uint32);
	void calc_energy_consumption(Uint32);
	void update_alarm_status(Uint32);
	void lay_egg(Uint32, Uint32);
	void produce_larva(Uint32);
	void test_if_larva_developped(Uint32);
	void create_ant(Uint32);
	void destroy(void);
};
