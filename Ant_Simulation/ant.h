#pragma once
#include "Ant_birth_info.h"
#include "Pheromone.h"
#include "Colony.h"
#include "Food.h"
#include "general_constants.h"
#include <list>
#include <vector>
#include "random_generator.h"

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
	//not been already registered in Table_of_items
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
	double _food_stored; //quantity of food that the ant's bringing
	double _max_food_storage;// maximum of this quantity
	double _distance_left;//distance left before the ant stops to think again
	double _max_distance_before_stop;

	void think(void);
	void restore_energy(Colony col);
	void attack(Game_item target);
	void set_pheromone(int,double,double);
	void destroy(void);
	void store_food (void);
	void take_food (void);
	//Random noise functions:
	 //These functions are use to add some random noise to a direction
	 //decision with divers probability laws...

	 //Add an uniform noise from -45° to 45°
	std::array<double,2> add_unif_noise_45 (std::array<double,2>);

	 //Add an uniform noise from -30° to 30°
	std::array<double,2> add_unif_noise_30 (std::array<double,2>);

	//Board interaction functions :
	 //These functions are used when a ant encountered a board of the game

	 //return the normal vector of the boards the ant is in collision with
	std::list<std::array<double,2>> return_normal_board (void);

	 //When an ant is in collision with a board this function gives
	 //the new direction the ant should take (list must be not empty)
	std::array<double,2> find_dir_from_board (std::list<std::array<double,2>>);

	 //But to make this choie of direction more natural, we have created
	 //this next function to add a bit more randomization to the direction
	 //and to choose according to the past direction the ant had
	std::array<double,2> rand_dir_from_board (std::array<double,2>);

	 //This function regroups all these previous functions to
	 //to manage the general reaction of an ant encountering a board
	void board_manager (std::list<std::array<double,2>>);

	bool _is_alive;
	bool _is_moving;
	bool _is_bringing_food;
	int _objective; //is the objective of the ant, for the moment
					//there are three possible :
					//		-scout (to find new foods)
					//		-go_back_to_colony (to bring back food to colony or
					//						  to go back to it to get energy...)
					//		-get_food (to go and take food from an already discovered food)

	Uint32 _time_to_move;//when an ant has stopped this indicates when it has to move again

	//list of olfactive collisions of the ant with pheromones

	std::list<std::shared_ptr<Pheromone>> _olf_coll_ph ;

	//lists of the objects in physical collisions with the ant

	std::list<std::shared_ptr<Ant>> _phys_coll_ant ;//collision with other ants
	std::list<std::shared_ptr<Colony>> _phys_coll_col ;//collision with colonies
	std::list<std::shared_ptr<Food>> _phys_coll_food ;//collision with food

	//AI functions

	void scout_AI (Uint32); //AI of the ant when it's trying to find food (is a scout)
	void back_AI (void); //AI of the ant when it wants to get back home
	void food_AI (void); //AI of the ant when it wants to go to a known food


};
