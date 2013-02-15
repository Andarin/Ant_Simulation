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
	Table_of_objects B(100);
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
	return 0;
}
