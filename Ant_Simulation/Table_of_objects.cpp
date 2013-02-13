#include "Table_of_objects.h"
#include <algorithm>	

Table_of_objects::Table_of_objects(int n)
{
	std::vector<std::shared_ptr<Hormone>> row_vect ;
	row_vect.resize(n);
	_pheromone_matrix.assign(n,row_vect);
}


Table_of_objects::~Table_of_objects(void)
{
}

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

void Table_of_objects::add_pheromone (std::shared_ptr<Hormone> p_pheromone){
	if (std::find(_pheromone_list.begin(), _pheromone_list.end(), p_pheromone) == _pheromone_list.end())
	_pheromone_list.push_back (p_pheromone);
}

std::list<std::shared_ptr<Ant>> Table_of_objects::get_ant_list(){
	return _ant_list ;
}

std::list<std::shared_ptr<Colony>> Table_of_objects::get_colony_list(){
	return _colony_list ;
}

std::list<std::shared_ptr<Food>> Table_of_objects::get_food_list(){
	return _food_list ;
}

std::list<std::shared_ptr<Hormone>> Table_of_objects::get_pheromone_list(){
	return _pheromone_list ;
}

std::vector<std::vector<std::shared_ptr<Hormone>>> Table_of_objects::get_pheromone_matrix(){
	return _pheromone_matrix ;
}