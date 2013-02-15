#include "Table_of_objects.h"

Table_of_objects::Table_of_objects()
{
}

Table_of_objects::Table_of_objects(int n, int size)
{
	std::vector<std::shared_ptr<Pheromone>> row_vect ;
	row_vect.resize(n);
	_pheromone_matrix.assign(n,row_vect);
	_nbr_sub = n;
	_board_size = size;
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
	double size_square ; //size of a square of the pheromone matrix
	size_square = ((double) _board_size) / ((double) _nbr_sub) ;
	x = (int) ((*p_pheromone)._pos._x/size_square);
	y = (int) ((*p_pheromone)._pos._y/size_square);
	if (_pheromone_matrix [x] [y] != NULL)
	(*(_pheromone_matrix [x] [y])).merge_pheromone(*p_pheromone);
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
	int x,y ;
	double size_square ; //size of a square of the pheromone matrix
	size_square = ((double) _board_size) / ((double) _nbr_sub) ;
	x = (int) ((*p_pheromone)._pos._x/size_square);
	y = (int) ((*p_pheromone)._pos._y/size_square);
	if (_pheromone_matrix[x] [y] == p_pheromone)
		_pheromone_matrix[x] [y] = NULL;
}

//Update functions :

void Table_of_objects::update_passive(Uint32 time,Uint32 time_step) {
	for (std::list<std::shared_ptr<Pheromone>>::iterator it=_pheromone_list.begin(); it != _pheromone_list.end(); ++it)	
	{
		(*(*it)).update(time,time_step);
	}

	for (std::list<std::shared_ptr<Colony>>::iterator it=_colony_list.begin(); it != _colony_list.end(); ++it)	
	{
		(*(*it)).update(time,time_step);
	}

	for (std::list<std::shared_ptr<Food>>::iterator it=_food_list.begin(); it != _food_list.end(); ++it)	
	{
		(*(*it)).update(time,time_step);
	}
	
}

