// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
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
	int _counter;

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
	//for the simple AI we add a counter to the pheromone
	//so the AI can find its way more easily
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

	 //Add a triangular noise from -30° to 30°
	std::array<double,2> add_triangle_noise_30 (std::array<double,2>);

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

	std::shared_ptr<Pheromone> _last_phero_targeted ;

	bool _is_alive;
	bool _is_moving;
	bool _get_back_colony;
	int _objective; //is the objective of the ant, for the moment
					//there are three possible :
					//		-scout (to find new foods)
					//		-go_back_to_colony (to bring back food to colony or
					//						  to go back to it to get energy...)
					//		-get_food (to go and take food from an already discovered food)

	//A varaible to test if the ant is in a colony
	bool _in_colony;

	//Another to test if an ant searching for food go to place where it is
	//supposed there is some food...
	bool _go_to_food;

	//when, because for instance there's no food anymore there, it should change the counter of a phero
	bool _change_phero_counter;

	Uint32 _time_to_move;//when an ant has stopped this indicates when it has to move again

	//list of olfactive collisions of the ant with pheromones

	std::list<std::shared_ptr<Pheromone>> _olf_coll_ph ;

	//list of the directions of the phero's that might be chosen

	std::list<std::array<double,2>> _phero_dir ;

	//list of the energies of these ones

	std::list<double> _phero_energies ;

	//lists of the objects in physical collisions with the ant

	std::list<std::shared_ptr<Ant>> _phys_coll_ant ;//collision with other ants
	std::list<std::shared_ptr<Colony>> _phys_coll_col ;//collision with colonies
	std::list<std::shared_ptr<Food>> _phys_coll_food ;//collision with food

	//AI functions

	void scout_AI (Uint32,int); //AI of the ant when it's trying to find a way
								// either to a colony or to a food
								// the int indicates the type of phero it sets
	void back_AI(); //AI of the ant when it wants to get back home
	void food_AI(); //AI of the ant when it wants to go to a known food
	void simple_back_AI(Uint32);
	void simple_food_AI(Uint32);

	 //Test if the ant should go back to the colony to full its energy

	void test_should_go_back_because_energy (void);

	 //Manage the decision of the ant when it encounters a board

	void what_should_do_when_meet_board (void);

	 //Manage the decision of the ant when it encounters a colony

	void what_should_do_when_meet_colony (void);

	 //Manage the decision of the ant when it encounters a food

	void what_should_do_when_meet_food (void);

	 //When an ant come to a place where it was supposed there is food
	 //and doesn't find anymore, so the ant modify the pheromone to indicate
	 //that other ants should not come at this place

	void what_to_do_when_food_disappear (void);

	 //Change type of AI depending on the objective of the ant

	void AI_chosen_according_to_objective (Uint32);

	 //common function for back_AI and food_AI to deal with the pheromones
	void dir_choice_according_to_phero (void) ;

	//Pheromone observation functions
	 //These functions deal with the interacton of the ant with the phero's

	 //Update the _phero_dir and _phero_energies lists

	void update_pheros_lists (void) ;

	 //From the list of the energies of the pheromones
	 //gives the random draw of the pheromone the ant
	 //should go to, return its rank in the list
	int rank_chosen_phero (void);
	
	 //gives the direction to the chosen pheromone with a random noise
	 //if there is no pheromone in the vision field return another direction
	std::array<double,2> direction_phero (void);

	 //to create a list of the smelled pheromones of type SIMPLE_AI_PHERO_BACK

	std::list<std::shared_ptr<Pheromone>> get_simple_back_phero (void);

	 //to create a list of the smelled pheromones of type SIMPLE_AI_PHERO_FOOD

	std::list<std::shared_ptr<Pheromone>> get_simple_food_phero (void);

};
