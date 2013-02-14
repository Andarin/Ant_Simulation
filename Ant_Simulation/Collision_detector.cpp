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

std::tuple<int,int> get_in_wich_square (Position pos, double sub) //get the square (of size sub)
{												//in the map where is located the object at pos
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
	std::list<std::shared_ptr<Pheromone>> list_of_pheromone = _environment.get_pheromone_list();//Obtain list of pheromone
	_map_ph_for_ant.clear();			//Initialisation of the map to an empty one
	while (!list_of_pheromone.empty())	//We'll fill that map with this pheromone list's items
	{
		//We take a pheromone from front of the list 
		std::shared_ptr<Pheromone> p_pheromone = list_of_pheromone.front();
		Pheromone pheromone = *p_pheromone;
		list_of_pheromone.pop_front();

		//We find out in which square (cf 1st commentary line) it is located
		Position pos_pheromone = pheromone._pos;
		double x = pos_pheromone._x;
		double y = pos_pheromone._y;
		double result_div_x = x / _sub_size_olf ;
		double result_div_y = y / _sub_size_olf ;
		int square_x = (int) x ;
		int square_y = (int) y ;
		std::tuple<int,int> square (square_x,square_y);

		//We place this pheromone in the map accordingly to the square it is located
		if (_map_ph_for_ant.find(square) != _map_ph_for_ant.end())
		{
			std::list<std::shared_ptr<Pheromone>> list_in_square = _map_ph_for_ant[square];
			list_in_square.push_back(p_pheromone);
			_map_ph_for_ant[square]=list_in_square;
		}
		else
		{
			std::list<std::shared_ptr<Pheromone>> list_in_square ;
			list_in_square.push_back(p_pheromone);
			_map_ph_for_ant[square] = list_in_square;
		};

	};
}

void Collision_detector::update_mafa(void)
{
	std::list<std::shared_ptr<Ant>> list_of_ant = _environment.get_ant_list();//Obtain list of ants
	_map_ant_for_ant.clear();			//Initialisation of the map to an empty one
	while (!list_of_ant.empty())	//We'll fill that map with this ant list's items
	{
		//We take a ant from front of the list 
		std::shared_ptr<Ant> p_ant = list_of_ant.front();
		Ant ant = *p_ant;
		list_of_ant.pop_front();

		//We get the position of this ant
		Position pos_ant = ant._pos;
		double x = pos_ant._x;
		double y = pos_ant._y;

		//We find out in which square (cf 1st commentary line) it is located
		double result_div_x = x / _sub_size_olf ;
		double result_div_y = y / _sub_size_olf ;
		int square_x = (int) x ;
		int square_y = (int) y ;
		std::tuple<int,int> square (square_x,square_y);

		//We place this pheromone in the map accordingly to the square it is located
		if (_map_ant_for_ant.find(square) != _map_ant_for_ant.end())
		{
			std::list<std::shared_ptr<Ant>> list_in_square = _map_ant_for_ant[square];
			list_in_square.push_back(p_ant);
			_map_ant_for_ant[square]=list_in_square;
		}
		else
		{
			std::list<std::shared_ptr<Ant>> list_in_square ;
			list_in_square.push_back(p_ant);
			_map_ant_for_ant[square] = list_in_square;
		};

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
	//We get the position of this ant
		Position pos_ant = ant._pos;
		double x = pos_ant._x;
		double y = pos_ant._y;
}