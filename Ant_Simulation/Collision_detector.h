#pragma once
#include "Table_of_objects.h"
#include <map>
#include <tuple>
#include <list>

class Collision_detector				//This object will be used to determine all the
{									//diverse collisions between the objects in the game.
public:									//It is build thanks to a Table_of_objects and three 
	Collision_detector(std::shared_ptr<Table_of_objects>, double, double, double);//doubles for the max radius
	~Collision_detector(void);			//of resp. olfactive, sight and touch collisions

	//Update functions :

	void update_environment(std::shared_ptr<Table_of_objects>); //for _environment
	void update_mpfa(void);		//for _map_ph_for_ant
	void update_mafa(void);		//for _map_ant_for_ant
	void update_mcfa(void);		//for _map_col_for_ant
	void update_mffa(void);		//for _map_food_for_ant
	void update_all(void);		//for all of them

	//Get functions :

	std::list<std::shared_ptr<Ant>> get_an_coll(std::shared_ptr<Ant>); //get a list of all ants in collision with our ant
	std::list<std::shared_ptr<Colony>> get_co_coll(std::shared_ptr<Ant>);//get a list of all colonies in collision with our ant
	std::list<std::shared_ptr<Food>> get_fo_coll(std::shared_ptr<Ant>);//get a list of all foods in collision with our ant
	std::list<std::shared_ptr<Pheromone>> get_ph_coll(std::shared_ptr<Ant>);//get a list of all pheromones in collision with our ant

	//Others...
	 //Get the square of a map of a certain double subdivision where position is
	std::tuple<int,int> get_in_wich_square (Position, double);

private:

	double _sub_size_olf;		//size of the sub for the olfactive collisions
	double _sub_size_view;		//size of the sub for the "sight or view" collisions
	double _sub_size_touch;		//size of the sub for the touch collisions

	std::shared_ptr<Table_of_objects> _environment;

	std::map<std::tuple<int,int>,std::list<std::shared_ptr<Pheromone>>> _map_ph_for_ant; //subdivision
					//of all the pheromones into groups to ease their collisions with an ant

	std::map<std::tuple<int,int>,std::list<std::shared_ptr<Ant>>> _map_ant_for_ant;//subdivision
					//of all the ants into groups to ease their collisions with an ant

	std::map<std::tuple<int,int>,std::list<std::shared_ptr<Colony>>> _map_col_for_ant;//subdivision
					//of all the colonies into groups to ease their collisions with an ant

	std::map<std::tuple<int,int>,std::list<std::shared_ptr<Food>>> _map_food_for_ant;//subdivision
					//of all the foods into groups to ease their collisions with an ant

};

