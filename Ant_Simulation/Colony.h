// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation

// This file is the factory for ants and the main game item
// the parameters can be given via a file read 
// the main object of the simulation is to find optimal parameters to
// handle the colony
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
	// API for hungry ants to demand for food
	double hand_out_food(double);
	// API for ants to store their digged food
	void store_food(double);
	// to increase or decrease egg production
	void change_egg_production(int);
	bool is_alive(void);

	//A list of the ant that have been recently created
	//Their positions will be define in table_of_items
	std::list<std::shared_ptr<Ant>> _buffer_fresh_ant;

	// functions to pass information to the HUD
	double get_size (void);
	double get_liquid_food(void);
	double get_solid_food(void);
	int get_queen_hp(void);
	int get_number_of_larvas(void);
	int _color;
	bool get_if_food_found(void);

private:
	// variables
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
	double _proba_that_ant_is_worker_not_solidier;
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

	// functions
	
	// ants cannot eat solid food, they need larvae to transform it to liquid
	// food; this function simulates this
	void transform_food(Uint32);
	// if there is not enough liquid food, the queen looses health points
	void check_if_queen_starves(Uint32);
	// calculate energy consumption of the colony; it depends on egg_production
	void calc_energy_consumption(Uint32);
	// an ant can pass an information about food and enemies to the colony
	void update_alarm_status(Uint32);
	void lay_egg(Uint32, Uint32);
	void produce_larva(Uint32);
	// checks if a larvae developped to an adult ant; if so, an ant is created
	void test_if_larva_developped(Uint32);
	void create_ant(Uint32);
	void destroy(void);
};
