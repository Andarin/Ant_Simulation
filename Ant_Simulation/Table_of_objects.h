#pragma once
#include "Ant.h"
#include "Colony.h"
#include "Food.h"
#include "Pheromone.h"
#include <list>
#include <vector>

class Table_of_objects					// This table regroup all the objects of the game
{								// It is created at the beginning and updated during the game
public:									// We use smart pointers to identify the objects
	Table_of_objects(int);		//The int input is the number of sudivisions of the matrix M
	~Table_of_objects(void);			// representing the map, i.e. dim M = n*n

	//Add functions :

	void add_ant (std::shared_ptr<Ant>);
	void add_colony (std::shared_ptr<Colony>);
	void add_food (std::shared_ptr<Food>);
	void add_pheromone (std::shared_ptr<Pheromone>);

	//Delete functions :

	void delete_ant (std::shared_ptr<Ant>);
	void delete_colony (std::shared_ptr<Colony>);
	void delete_food (std::shared_ptr<Food>);
	void delete_pheromone (std::shared_ptr<Pheromone>);

	//Get functions :

	std::list<std::shared_ptr<Ant>> get_ant_list();
	std::list<std::shared_ptr<Colony>> get_colony_list();
	std::list<std::shared_ptr<Food>> get_food_list();
	std::list<std::shared_ptr<Pheromone>> get_pheromone_list();
	std::vector<std::vector<std::shared_ptr<Pheromone>>> get_pheromone_matrix();

private:

	//Lists :

	std::list<std::shared_ptr<Ant>> _ant_list;
	std::list<std::shared_ptr<Colony>> _colony_list;
	std::list<std::shared_ptr<Food>> _food_list;
	std::list<std::shared_ptr<Pheromone>> _pheromone_list;

	//Pheromone position matrix :

	std::vector<std::vector<std::shared_ptr<Pheromone>>> _pheromone_matrix ;

};

