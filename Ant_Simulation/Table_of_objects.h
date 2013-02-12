#pragma once
#include "Ant.h"
#include "Colony.h"
#include "Food.h"
#include <list>

class Table_of_objects
{
public:
	Table_of_objects(void);
	~Table_of_objects(void);
	void add_ant (std::shared_ptr<Ant>);
	void add_colony (std::shared_ptr<Colony>);
	void add_food (std::shared_ptr<Food>);
	std::list<std::shared_ptr<Ant>> get_ant_list();
	std::list<std::shared_ptr<Colony>> get_colony_list();
	std::list<std::shared_ptr<Food>> get_food_list();

private:
	std::list<std::shared_ptr<Ant>> _ant_list;
	std::list<std::shared_ptr<Colony>> _colony_list;
	std::list<std::shared_ptr<Food>> _food_list;
};

