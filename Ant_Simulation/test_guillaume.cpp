#include "Table_of_objects.h"
#include <windows.h>
#include <SDL.h>
#include <iostream>

int main(int argc, char** argv){
	Ant_birth_info Ai ;
	Ai._color = 767 ;
	auto shared_pointer_ant = std::make_shared<Ant>(Ai);
	Table_of_objects B;
	B.add_ant(shared_pointer_ant);
	std::list<std::shared_ptr<Ant>> l = B.get_ant_list();
	std::list<std::shared_ptr<Ant>>::iterator it = l.begin();
	std::advance(it, 0);
	std::shared_ptr<Ant> p = *it ;
	(*p)._color = 555 ;
	return 0;
}