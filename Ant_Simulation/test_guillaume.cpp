#include "Table_of_objects.h"
#ifdef _WIN32
	#include "windows.h"
	#include <SDL.h>
#else
	#include <SDL/SDL.h>
#endif
#include <iostream>
#include <tuple>

int main(int argc, char** argv){

	Ant_birth_info Ai ;
	Ai._color = 767 ;
	auto shared_pointer_ant = std::make_shared<Ant>(Ai);

	Table_of_objects B(20,50);
	B.add_ant(shared_pointer_ant);
	B.add_ant(shared_pointer_ant);

	std::list<std::shared_ptr<Ant>> l = B._ant_list;
	std::list<std::shared_ptr<Ant>>::iterator it = l.begin();
	std::advance(it, 0);
	std::shared_ptr<Ant> p = *it ;
	(*p)._color = 555 ;

	std::vector<std::vector<std::shared_ptr<Pheromone>>> M = B._pheromone_matrix;
	std::shared_ptr<Pheromone> pp = M[0][0];
	B.delete_ant(shared_pointer_ant);
	bool bb = (pp == NULL);

	double aaa = 3.678;
	double ccc = aaa/1.233333;
	int bbb= (int) aaa;

	if (bbb == 3)
	{std::list<double> lll ;
	lll.push_back(aaa);}

	Game_object_birth_info g ;
	(g._pos)._x = 34.5;
	(g._pos)._y = 32.7;
	g._energy = 1 ;
	g._energy_consumption_per_m = 1 ;
	auto phero = std::make_shared<Pheromone> (g,5) ;
	auto phero_1  = std::make_shared<Pheromone> (g,5) ;

	B.add_pheromone(phero);
	B.add_pheromone(phero_1);

	B.update_passive(0,40000);
	B.update_passive(0,40000);
	B.update_passive(0,41000);
	B.update_passive(0,41000);
	
	B.delete_pheromone(phero_1) ;
	B.delete_pheromone(phero);

	return 0;
}
