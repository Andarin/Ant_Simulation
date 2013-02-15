#include "Collision_detector.h"

Collision_detector::Collision_detector(Table_of_objects env, double solf, double sview, double stouch)
{
	_environment = env;
	_sub_size_olf = solf;
	_sub_size_view = sview;
	_sub_size_touch = stouch;
}


Collision_detector::~Collision_detector(void)
{

}

std::tuple<int,int> Collision_detector::get_in_wich_square (Position pos, double sub)
										//get the square (of size sub)
{										//in the map where is located the object at pos
	double x = pos._x;
	double y = pos._y;
	double result_div_x = x / sub ;
	double result_div_y = y / sub ;
	int square_x = (int) x ;
	int square_y = (int) y ;
	std::tuple<int,int> square (square_x,square_y);
	return square;
}

//Update functions

void Collision_detector::update_environment(Table_of_objects env)
{
	_environment = env;
}

void Collision_detector::update_mpfa(void)//This map will be a subdivision of the game surface by squares of size equals to _sub_size_olf
{					
	_map_ph_for_ant.clear();	//Initialisation of the map to an empty one
	//We'll fill that map with this pheromone list's items
	for (std::list<std::shared_ptr<Pheromone>>::iterator it= (_environment._pheromone_list).begin(); it != (_environment._pheromone_list).end(); ++it)
	{
		//We take at the iterator's place 
		std::shared_ptr<Pheromone> p_pheromone = *it;
		Pheromone pheromone = *p_pheromone;

		//We find out in which square (cf 1st commentary line) it is located
		Position pos_pheromone = pheromone._pos;
		std::tuple<int,int> square = get_in_wich_square (pos_pheromone, _sub_size_olf);
		
		//We place this pheromone in the map accordingly to the square it is located
		(_map_ph_for_ant.at(square)).push_back(p_pheromone);
	};
}

void Collision_detector::update_mafa(void)
{
	_map_ant_for_ant.clear();	//Initialisation of the map to an empty one
	//We'll fill that map with this ant list's items
	for (std::list<std::shared_ptr<Ant>>::iterator it= (_environment._ant_list).begin(); it != (_environment._ant_list).end(); ++it)	
	{
		//We take a ant from front of the list 
		std::shared_ptr<Ant> p_ant = *it;
		Ant ant = *p_ant;

		//We find out in which square (cf 1st commentary line) it is located
		Position pos_ant = ant._pos;
		std::tuple<int,int> square = get_in_wich_square (pos_ant, _sub_size_olf);

		//We place this pheromone in the map accordingly to the square it is located
		_map_ant_for_ant.at(square).push_back(p_ant);
	};
}

void Collision_detector::update_mcfa(void)
{

}

void Collision_detector::update_mffa(void)
{

}

void Collision_detector::update_all(void)
{

}

//Get functions

std::list<std::shared_ptr<Pheromone>> Collision_detector::get_ph_coll(std::shared_ptr<Ant> p_ant)
{
	//We get first the square where the ant is
	Ant ant = *p_ant ;
	Position pos = ant._pos ;
	std::tuple<int,int> square = get_in_wich_square (pos,_sub_size_olf);


	//Then we look in the squares arround its to search for collisions
	int x,y,i,j ;
	std::tie (x,y) = square;
	std::list<std::shared_ptr<Pheromone>> res;
	for (i=-1; i<2; i++)
	{
		for (j=-1; j<2; j++)
		{
			std::tuple<int,int> sq (x,y) ;
			for (std::list<std::shared_ptr<Pheromone>>::iterator it= (_map_ph_for_ant.at(sq)).begin(); it != (_map_ph_for_ant.at(sq)).end(); ++it)
			{
				res.push_back(*it);
			};
		};
	};
	return res ;

}