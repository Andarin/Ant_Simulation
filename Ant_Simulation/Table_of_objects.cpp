#include "Table_of_objects.h"


Table_of_objects::Table_of_objects(void)
{
}


Table_of_objects::~Table_of_objects(void)
{
}

void Table_of_objects::add_ant (std::shared_ptr<Ant> p_ant){
	_ant_list.push_back (p_ant);
}

void Table_of_objects::add_colony (std::shared_ptr<Colony> p_colony){
	_colony_list.push_back (p_colony);
}

void Table_of_objects::add_food (std::shared_ptr<Food> p_food){
	_food_list.push_back (p_food);
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