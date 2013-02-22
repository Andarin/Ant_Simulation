#include "Table_of_objects.h"
#include "Collision_detector.h"
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

	auto p_table = std::make_shared<Table_of_objects>(20,50);
	Collision_detector C(p_table, 5,5,5);
	(*p_table).add_ant(shared_pointer_ant);
	(*p_table).add_ant(shared_pointer_ant);

	std::list<std::shared_ptr<Ant>> l = (*p_table)._ant_list;
	std::list<std::shared_ptr<Ant>>::iterator it = l.begin();
	std::advance(it, 0);
	std::shared_ptr<Ant> p = *it ;
	(*p)._color = 555 ;

	std::vector<std::vector<std::shared_ptr<Pheromone>>> M = (*p_table)._pheromone_matrix;
	std::shared_ptr<Pheromone> pp = M[0][0];
	(*p_table).delete_ant(shared_pointer_ant);
	bool bb = (pp == NULL);

	double aaa = 3.678;
	double ccc = aaa/1.233333;
	int bbb= (int) aaa;

	if (bbb == 3)
	{std::list<double> lll ;
	lll.push_back(aaa);}

	Game_object_birth_info g ;
	(g._pos)._x = 34.5;
	(g._pos)._z = 32.7;
	g._energy = 1 ;
	g._energy_consumption_per_m = 1 ;
	auto phero = std::make_shared<Pheromone> (g,5) ;
	auto phero_1  = std::make_shared<Pheromone> (g,5) ;

	(*p_table).add_pheromone(phero);
	(*p_table).add_pheromone(phero_1);

	(*p_table).update_passive(0,40000);
	(*p_table).update_passive(0,40000);
	(*p_table).update_passive(0,41000);
	(*p_table).update_passive(0,41000);
	
	(*p_table).delete_pheromone(phero_1) ;
	(*p_table).delete_pheromone(phero);

	Colony_birth_info Ci;
	Ci._pos._x = 30;
	Ci._pos._z = 30;
	auto p_col = std::make_shared<Colony>(Ci);

	(*p_table).add_colony(p_col);
	(*p_col)._buffer_fresh_ant.push_back(shared_pointer_ant);
	(*p_table).update_passive(0,123456);

	auto phero_2  = std::make_shared<Pheromone> (g,5) ;
	(*p_table).add_pheromone(phero_2);

	C.update_all(0,1000);

	auto lllll = C.get_ph_coll(shared_pointer_ant);

	std::array<double,2> tab;
	tab[0] = 1;
	tab[1] = 2;

	return 0;
}
