// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Table_of_items.h"

Table_of_items::Table_of_items()
{
}

Table_of_items::Table_of_items(int n, int size)
{
	std::vector<std::shared_ptr<Pheromone>> row_vect ;
	row_vect.resize(n);
	_pheromone_matrix.assign(n,row_vect);
	_nbr_sub = n;
	_board_size = size;
}


Table_of_items::~Table_of_items(void)
{
}


//Add functions :

void Table_of_items::add_ant (std::shared_ptr<Ant> p_ant){
	if (std::find(_ant_list.begin(), _ant_list.end(), p_ant) == _ant_list.end())
		_ant_list.push_back (p_ant);
}

void Table_of_items::add_colony (std::shared_ptr<Colony> p_colony){
	if (std::find(_colony_list.begin(), _colony_list.end(), p_colony) == _colony_list.end())
		_colony_list.push_back (p_colony);
}

void Table_of_items::add_obstacle (std::shared_ptr<Obstacle> p_obstacle){
	if (std::find(_obstacle_list.begin(), _obstacle_list.end(), p_obstacle) == _obstacle_list.end())
		_obstacle_list.push_back (p_obstacle);
}

void Table_of_items::add_food (std::shared_ptr<Food> p_food){
	if (std::find(_food_list.begin(), _food_list.end(), p_food) == _food_list.end())
		_food_list.push_back (p_food);
}

//Delete functions :

void Table_of_items::delete_ant (std::shared_ptr<Ant> p_ant){
	_ant_list.remove(p_ant) ;
}

void Table_of_items::delete_colony (std::shared_ptr<Colony> p_colony){
	_colony_list.remove(p_colony) ;
}

void Table_of_items::delete_food (std::shared_ptr<Food> p_food){
	_food_list.remove(p_food) ;
}

void Table_of_items::delete_obstacle (std::shared_ptr<Obstacle> p_obstacle){
	_obstacle_list.remove(p_obstacle) ;
}

// speed optimized functions table_of_item functions

void Table_of_items::add_pheromone(std::shared_ptr<Pheromone> p_pheromone)
{
	//We have also to update the matrix of pheromones
	int x,z ;
	double size_square ; //size of a square of the pheromone matrix
	size_square = ((double) _board_size) / ((double) _nbr_sub) ;
	x = (int) ((*p_pheromone)._pos._x/size_square);
	z = (int) ((*p_pheromone)._pos._z/size_square);
	//If there is already a pheromone at this place in the matrix
	//we merge the new one with the ancient one (without adding former)
	int key = _nbr_sub*x + z;
	std::pair<std::map<int,std::shared_ptr<Pheromone>>::iterator,bool> ret;
	ret = _phero_map.insert ( std::pair<int,std::shared_ptr<Pheromone>>(key,p_pheromone) );
	if (ret.second==false) {
		// there is already a pheromone at this place, so merge the new pheromone with the
		// old one where ret.first->second is a pointer to the old pheromone
		(*ret.first->second).merge_pheromone(p_pheromone);
	}
}

void Table_of_items::update_passive(Uint32 time,Uint32 time_step) 
{
	//We decided not to use the delete function to reduce the complexity
	//Indeed, if we used this, we would have a quadratic complexity
	//because delete has already a linear complexity. So our function
	//here has a linear complexity because there's only one 'for' iteration.
	std::map<int,std::shared_ptr<Pheromone>>::iterator it = _phero_map.begin();
	for (it=_phero_map.begin(); it!=_phero_map.end(); ++it)
	{
		if ((*it->second).is_alive())
			(*it->second).update(time,time_step);
		else
		{
			auto it_1 = it;
			--it;
			_phero_map.erase(it_1);
		}
	}

	for (std::list<std::shared_ptr<Colony>>::iterator it=_colony_list.begin(); it != _colony_list.end(); ++it)	
	{
		if ((*(*it)).is_alive())
		{
			(*(*it)).update(time,time_step);
			while (!(*(*it))._buffer_fresh_ant.empty())
			{
				std::shared_ptr<Ant> p_ant = ((*(*it))._buffer_fresh_ant.back());
				(*p_ant)._pos = (*(*it))._pos;
				add_ant(p_ant);
				(*(*it))._buffer_fresh_ant.pop_back();
			}
		}
		else
		{
			//If we erased now at that it iterator, it would be problematic
			//because in the 'for' iteration, the path to the next element
			//would be lost. So that's why we step back with --it before erase
			auto it_1 = it;
			--it;
			_colony_list.erase(it_1);
		}
	}

	for (std::list<std::shared_ptr<Food>>::iterator it=_food_list.begin(); it != _food_list.end(); ++it)	
	{
		if ((*(*it)).is_alive())
			(*(*it)).update(time,time_step);
		else
		{
			//If we erased now at that it iterator, it would be problematic
			//because in the 'for' iteration, the path to the next element
			//would be lost. So that's why we step back with --it before erase
			auto it_1 = it;
			--it;
			_food_list.erase(it_1);
		}
	}
}



// old table_of_item functions - functional but too slow

//void Table_of_items::delete_pheromone (std::shared_ptr<Pheromone> p_pheromone){
//	_pheromone_list.remove(p_pheromone) ;
//	int x,z ;
//	double size_square ; //size of a square of the pheromone matrix
//	size_square = ((double) _board_size) / ((double) _nbr_sub) ;
//	x = (int) ((*p_pheromone)._pos._x/size_square);
//	z = (int) ((*p_pheromone)._pos._z/size_square);
//	if (_pheromone_matrix[x] [z] == p_pheromone)
//		_pheromone_matrix[x] [z] = NULL;
//}

////Update functions :
//
//void Table_of_items::update_passive(Uint32 time,Uint32 time_step) {
//	//We decided not to use the delete function to reduce the complexity
//	//Indeed, if we used this, we would have a quadratic complexity
//	//because delete has already a linear complexity. So our function
//	//here has a linear complexity because there's only one 'for' iteration.
//	for (std::list<std::shared_ptr<Pheromone>>::iterator it=_pheromone_list.begin(); it != _pheromone_list.end(); ++it)	
//	{
//		if ((*(*it)).is_alive())
//			(*(*it)).update(time,time_step);
//		else
//		{
//			std::shared_ptr<Pheromone> p_pheromone = *it ;
//
//			//And we have also to delete it from the matrix if it's there
//			int x,z ;
//			double size_square ; //size of a square of the pheromone matrix
//			size_square = ((double) _board_size) / ((double) _nbr_sub) ;
//			x = (int) ((*p_pheromone)._pos._x/size_square);
//			z = (int) ((*p_pheromone)._pos._z/size_square);
//			if (_pheromone_matrix[x] [z] == p_pheromone)
//				_pheromone_matrix[x] [z] = NULL;
//
//			//If we erased now at that it iterator, it would be problematic
//			//because in the 'for' iteration, the path to the next element
//			//would be lost. So that's why we step back with --it before erase
//			auto it_1 = it;
//			--it;
//			_pheromone_list.erase(it_1);
//		}
//	}
//
//	for (std::list<std::shared_ptr<Colony>>::iterator it=_colony_list.begin(); it != _colony_list.end(); ++it)	
//	{
//		if ((*(*it)).is_alive())
//		{
//			(*(*it)).update(time,time_step);
//			while (!(*(*it))._buffer_fresh_ant.empty())
//			{
//				std::shared_ptr<Ant> p_ant = ((*(*it))._buffer_fresh_ant.back());
//				(*p_ant)._pos = (*(*it))._pos;
//				add_ant(p_ant);
//				(*(*it))._buffer_fresh_ant.pop_back();
//			}
//		}
//		else
//		{
//			//If we erased now at that it iterator, it would be problematic
//			//because in the 'for' iteration, the path to the next element
//			//would be lost. So that's why we step back with --it before erase
//			auto it_1 = it;
//			--it;
//			_colony_list.erase(it_1);
//		}
//	}
//
//	for (std::list<std::shared_ptr<Food>>::iterator it=_food_list.begin(); it != _food_list.end(); ++it)	
//	{
//		if ((*(*it)).is_alive())
//			(*(*it)).update(time,time_step);
//		else
//		{
//			//If we erased now at that it iterator, it would be problematic
//			//because in the 'for' iteration, the path to the next element
//			//would be lost. So that's why we step back with --it before erase
//			auto it_1 = it;
//			--it;
//			_food_list.erase(it_1);
//		}
//	}
//	
//}
//
// old delete function

//void Table_of_items::add_pheromone (std::shared_ptr<Pheromone> p_pheromone){
//
//	if (std::find(_pheromone_list.begin(), _pheromone_list.end(), p_pheromone) == _pheromone_list.end())
//	{	
//		//We have also to update the matrix of pheromones
//		int x,z ;
//		double size_square ; //size of a square of the pheromone matrix
//		size_square = ((double) _board_size) / ((double) _nbr_sub) ;
//		x = (int) ((*p_pheromone)._pos._x/size_square);
//		z = (int) ((*p_pheromone)._pos._z/size_square);
//		//If there is already a pheromone at this place in the matrix
//		//we merge the new one with the ancient one (without adding former)
//		if (_pheromone_matrix [x] [z] != NULL)
//		{
//			(*(_pheromone_matrix [x] [z])).merge_pheromone(p_pheromone);
//		}
//		//Otherwise, we add this pheromone as we did it with the other objects
//		else
//		{
//			_pheromone_matrix [x] [z] = p_pheromone;
//			_pheromone_list.push_back (p_pheromone);
//		}
//	}
//}