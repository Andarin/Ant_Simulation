#include "Collision_detector.h"

Collision_detector::Collision_detector(std::shared_ptr<Table_of_items> env, double solf, double sview, double stouch)
{
	_environment = env;
	_sub_size_olf = solf;
	_sub_size_view = sview;
	_sub_size_touch = stouch;
}


Collision_detector::~Collision_detector(void)
{

}

std::tuple<int,int> Collision_detector::get_in_which_square (Position pos, double sub)
										//get the square (of size sub)
{										//in the map where is located the object at pos
	double x = pos._x;
	double z = pos._z;
	double result_div_x = x / sub ;
	double result_div_z = z / sub ;
	int square_x = (int) result_div_x ;
	int square_z = (int) result_div_z ;
	std::tuple<int,int> square (square_x,square_z);
	return square;
}

double Collision_detector::square_distance(Position pos1, Position pos2)
{
	double x = pos1._x - pos2._x;
	double z = pos1._z - pos2._z;
	return (x*x + z*z);
}

//Update functions

void Collision_detector::update_environment(std::shared_ptr<Table_of_items> env)
{
	_environment = env;
}

void Collision_detector::update_mpfa(void)//This map will be a subdivision of the game surface by squares of size equals to _sub_size_olf
{					
	_map_ph_for_ant.clear();	//Initialisation of the map to an empty one
	//We'll fill that map with this pheromone list's items
	for (std::list<std::shared_ptr<Pheromone>>::iterator it= ((*_environment)._pheromone_list).begin(); it != ((*_environment)._pheromone_list).end(); ++it)
	{
		//We take at the iterator's place 
		std::shared_ptr<Pheromone> p_pheromone = *it;
		Pheromone pheromone = *p_pheromone;

		//We find out in which square (cf 1st commentary line) it is located
		Position pos_pheromone = pheromone._pos;
		std::tuple<int,int> square = get_in_which_square (pos_pheromone, _sub_size_olf);
		
		//We place this pheromone in the map accordingly to the square it is located
		if (_map_ph_for_ant.count(square) == 1)
			(_map_ph_for_ant.at(square)).push_back(p_pheromone);
		else
		{
			std::list<std::shared_ptr<Pheromone>> l;
			l.push_back(p_pheromone);
			_map_ph_for_ant.insert(std::pair<std::tuple<int,int>,std::list<std::shared_ptr<Pheromone>>>(square,l));
		}
	}
}

void Collision_detector::update_mafa(void)
{
	_map_ant_for_ant.clear();	//Initialisation of the map to an empty one
	//We'll fill that map with this ant list's items
	for (std::list<std::shared_ptr<Ant>>::iterator it= ((*_environment)._ant_list).begin(); it != ((*_environment)._ant_list).end(); ++it)	
	{
		//We take a ant from front of the list 
		std::shared_ptr<Ant> p_ant = *it;
		Ant ant = *p_ant;

		//We find out in which square (cf 1st commentary line) it is located
		Position pos_ant = ant._pos;
		std::tuple<int,int> square = get_in_which_square (pos_ant, _sub_size_olf);

		//We place this ant in the map accordingly to the square it is located
		if (_map_ant_for_ant.count(square) == 1)
			(_map_ant_for_ant.at(square)).push_back(p_ant);
		else
		{
			std::list<std::shared_ptr<Ant>> l;
			l.push_back(p_ant);
			_map_ant_for_ant.insert(std::pair<std::tuple<int,int>,std::list<std::shared_ptr<Ant>>>(square,l));
		}
	}
}

void Collision_detector::update_mcfa(void)
{
	_map_col_for_ant.clear();	//Initialisation of the map to an empty one
	//We'll fill that map with this ant list's items
	for (std::list<std::shared_ptr<Colony>>::iterator it= ((*_environment)._colony_list).begin(); it != ((*_environment)._colony_list).end(); ++it)	
	{
		//We take a ant from front of the list 
		std::shared_ptr<Colony> p_colony = *it;
		Colony colony = *p_colony;

		//We find out in which square (cf 1st commentary line) it is located
		Position pos_colony = colony._pos;
		std::tuple<int,int> square = get_in_which_square (pos_colony, _sub_size_olf);

		//We place this colony in the map accordingly to the square it is located
		if (_map_col_for_ant.count(square) == 1)
			(_map_col_for_ant.at(square)).push_back(p_colony);
		else
		{
			std::list<std::shared_ptr<Colony>> l;
			l.push_back(p_colony);
			_map_col_for_ant.insert(std::pair<std::tuple<int,int>,std::list<std::shared_ptr<Colony>>>(square,l));
		}
	}
}

void Collision_detector::update_mffa(void)
{
	_map_food_for_ant.clear();	//Initialisation of the map to an empty one
	//We'll fill that map with this ant list's items
	for (std::list<std::shared_ptr<Food>>::iterator it= ((*_environment)._food_list).begin(); it != ((*_environment)._food_list).end(); ++it)	
	{
		//We take a ant from front of the list 
		std::shared_ptr<Food> p_food = *it;
		Food food = *p_food;

		//We find out in which square (cf 1st commentary line) it is located
		Position pos_food = food._pos;
		std::tuple<int,int> square = get_in_which_square (pos_food, _sub_size_olf);

		//We place this pheromone in the map accordingly to the square it is located
		if (_map_food_for_ant.count(square) == 1)
			(_map_food_for_ant.at(square)).push_back(p_food);
		else
		{
			std::list<std::shared_ptr<Food>> l;
			l.push_back(p_food);
			_map_food_for_ant.insert(std::pair<std::tuple<int,int>,std::list<std::shared_ptr<Food>>>(square,l));
		}
	}
}
 
void Collision_detector::update_active(Uint32 time,Uint32 time_step)//for the moment only the ants are 'active'
{
	for (std::list<std::shared_ptr<Ant>>::iterator it= (*_environment)._ant_list.begin(); it != (*_environment)._ant_list.end(); ++it)
	{
		if ((*(*it)).is_alive())
		{
			std::list<std::shared_ptr<Ant>> coll_between_ants ;
			(*(*it)).update(time,time_step,coll_between_ants,get_co_coll(*it),get_fo_coll(*it));
			if (!((*(*it)).is_moving()))
				(*(*it)).update_ph(get_ph_coll(*it));
			while (!(*(*it))._buffer_fresh_phero.empty())
			{
				std::shared_ptr<Pheromone> p_pheromone = (((*(*it))._buffer_fresh_phero).back());
				(*p_pheromone)._pos = (*(*it))._pos;
			}
		}
		else
		{
			//If we erased now at that it iterator, it would be problematic
			//because in the 'for' iteration, the path to the next element
			//would be lost. So that's why we step back with --it before erase
			auto it_1 = it;
			--it;
			((*_environment)._ant_list).erase(it_1);
		}
	}
}

void Collision_detector::update_all(Uint32 time,Uint32 time_step)
{
	update_mpfa();
	update_mafa();
	update_mcfa();
	update_mffa();
	update_active(time,time_step);
}

//Get functions

std::list<std::shared_ptr<Pheromone>> Collision_detector::get_ph_coll(std::shared_ptr<Ant> p_ant)
{
	//We get first the square where the ant is
	Ant ant = *p_ant ;
	Position pos = ant._pos ;
	std::tuple<int,int> square = get_in_which_square (pos,_sub_size_olf);


	//Then we look in the squares arround its to search for collisions
	int x,z,i;
	std::tie (x,z) = square;
	std::list<std::shared_ptr<Pheromone>> res;
	for (i=0; i<9; i++)
	{
		std::tuple<int,int> sq (x+ i%3-1,z+ i/3-1) ;
		if (_map_ph_for_ant.count(sq) == 1)
		{
			for (std::list<std::shared_ptr<Pheromone>>::iterator it= (_map_ph_for_ant.at(sq)).begin(); it != (_map_ph_for_ant.at(sq)).end(); ++it)
			{
				double r = (*(*it)).get_size();
				if ((square_distance ((*p_ant)._pos, (*(*it))._pos) < r*r) && (*(*it)).is_alive())
					res.push_back(*it);
			}
		}
	}
	return res ;

}

std::list<std::shared_ptr<Ant>> Collision_detector::get_an_coll(std::shared_ptr<Ant> p_ant)
{
	//We get first the square where the ant is
	Ant ant = *p_ant ;
	Position pos = ant._pos ;
	std::tuple<int,int> square = get_in_which_square (pos,_sub_size_touch);


	//Then we look in the squares arround its to search for collisions
	int x,z,i ;
	std::tie (x,z) = square;
	std::list<std::shared_ptr<Ant>> res;
	for (i=0; i<9; i++)
	{
		std::tuple<int,int> sq (x+ i%3-1,z+ i/3-1) ;
		if (_map_ant_for_ant.count(sq) == 1)
		{
			for (std::list<std::shared_ptr<Ant>>::iterator it= (_map_ant_for_ant.at(sq)).begin(); it != (_map_ant_for_ant.at(sq)).end(); ++it)
			{
				double r = ((*(*it)).get_size()) + ((*p_ant).get_size());
				if ((square_distance ((*p_ant)._pos, (*(*it))._pos) < r*r) && (*(*it)).is_alive())
					res.push_back(*it);
			}
		}
	}
	return res ;

}

std::list<std::shared_ptr<Colony>> Collision_detector::get_co_coll(std::shared_ptr<Ant> p_ant)
{
	//We get first the square where the ant is
	Ant ant = *p_ant ;
	Position pos = ant._pos ;
	std::tuple<int,int> square = get_in_which_square (pos,_sub_size_olf);


	//Then we look in the squares arround its to search for collisions
	int x,z,i ;
	std::tie (x,z) = square;
	std::list<std::shared_ptr<Colony>> res;
	for (i=0; i<9; i++)
	{
		std::tuple<int,int> sq (x+ i%3-1,z+ i/3-1) ;
		if (_map_col_for_ant.count(sq) == 1)
		{
			for (std::list<std::shared_ptr<Colony>>::iterator it= (_map_col_for_ant.at(sq)).begin(); it != (_map_col_for_ant.at(sq)).end(); ++it)
			{
				double r = (*(*it)).get_size() + (*p_ant).get_size();
				if ((square_distance ((*p_ant)._pos, (*(*it))._pos) < r*r) && (*(*it)).is_alive())
					res.push_back(*it);
			}
		}
	}
	return res ;

}

std::list<std::shared_ptr<Food>> Collision_detector::get_fo_coll(std::shared_ptr<Ant> p_ant)
{
	//We get first the square where the ant is
	Ant ant = *p_ant ;
	Position pos = ant._pos ;
	std::tuple<int,int> square = get_in_which_square (pos,_sub_size_olf);


	//Then we look in the squares arround its to search for collisions
	int x,z,i ;
	std::tie (x,z) = square;
	std::list<std::shared_ptr<Food>> res;
	for (i=0; i<9; i++)
	{
		std::tuple<int,int> sq (x+ i%3-1,z+ i/3-1) ;
		if (_map_food_for_ant.count(sq) == 1)
		{
			for (std::list<std::shared_ptr<Food>>::iterator it= (_map_food_for_ant.at(sq)).begin(); it != (_map_food_for_ant.at(sq)).end(); ++it)
			{
				double r = (*(*it)).get_size() + (*p_ant).get_size();
				if ((square_distance ((*p_ant)._pos, (*(*it))._pos) < r*r) && (*(*it)).is_alive())
					res.push_back(*it);
			}
		}
	}
	return res ;

}