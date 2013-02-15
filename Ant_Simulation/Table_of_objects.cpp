#include "Table_of_objects.h"

Table_of_objects::Table_of_objects()
{
}

Table_of_objects::Table_of_objects(int n, int size)
{
	std::vector<std::shared_ptr<Pheromone>> row_vect ;
	row_vect.resize(n);
	_pheromone_matrix.assign(n,row_vect);
}


Table_of_objects::~Table_of_objects(void)
{
}

//Add functions :

void Table_of_objects::add_ant (std::shared_ptr<Ant> p_ant){
	if (std::find(_ant_list.begin(), _ant_list.end(), p_ant) == _ant_list.end())
		_ant_list.push_back (p_ant);
}

void Table_of_objects::add_colony (std::shared_ptr<Colony> p_colony){
	if (std::find(_colony_list.begin(), _colony_list.end(), p_colony) == _colony_list.end())
		_colony_list.push_back (p_colony);
}

void Table_of_objects::add_food (std::shared_ptr<Food> p_food){
	if (std::find(_food_list.begin(), _food_list.end(), p_food) == _food_list.end())
		_food_list.push_back (p_food);
}

void Table_of_objects::add_pheromone (std::shared_ptr<Pheromone> p_pheromone){

	//We first update the list of pheromones as we did it previously for the other lists
	if (std::find(_pheromone_list.begin(), _pheromone_list.end(), p_pheromone) == _pheromone_list.end())
		_pheromone_list.push_back (p_pheromone);

	//But we have also to update the matrix of pheromones
	int x,y ;
	x = (int) (*p_pheromone)._pos._x;
	y = (int) (*p_pheromone)._pos._y;


}

//Delete functions :

void Table_of_objects::delete_ant (std::shared_ptr<Ant> p_ant){
	_ant_list.remove(p_ant) ;
}

void Table_of_objects::delete_colony (std::shared_ptr<Colony> p_colony){
	_colony_list.remove(p_colony) ;
}

void Table_of_objects::delete_food (std::shared_ptr<Food> p_food){
	_food_list.remove(p_food) ;
}

void Table_of_objects::delete_pheromone (std::shared_ptr<Pheromone> p_pheromone){
	_pheromone_list.remove(p_pheromone) ;
}


