// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Ant_Sim.h"

Ant_Sim::Ant_Sim(void)
{
	_time_remaining = read_play_time_from_file(FILE_NAME)*1000;
	_sim_time_step = 10; // in milli seconds
	_max_size_of_pheromone = 300;
	_max_size_of_corps = 100;

	// boolean checks
	_running = true;
	_countdown_on = false;

	// graphic related variables
	_round_cnt = 0;
	_keystates = SDL_GetKeyState( NULL );

	// load related variables
	_is_replay = false;

	// just for testing / not important
	//_ant_number = 1000;
	//_ant_posx = new float[_ant_number];
	//_ant_posz = new float[_ant_number];
	//_ant_posy = 2;
	//_ant_size = 10;
	//_ant_angley = 180;
}

Ant_Sim::~Ant_Sim(void)
{
}

void Ant_Sim::init(void)
{
	_table_items = std::make_shared<Table_of_items>(500, BOARD_SIZE);
	_coll_dect = std::make_shared<Collision_detector>(_table_items, 
							_max_size_of_pheromone, _max_size_of_vision, _max_size_of_corps);
	if (!_is_replay)
	{
		add_colony();
		add_start_food(50);
		add_obstacle(150,BOARD_SIZE-200,0,BOARD_SIZE-200);
		add_obstacle(100,BOARD_SIZE-200,0,BOARD_SIZE-300);
		add_obstacle(50,BOARD_SIZE-300,0,BOARD_SIZE-300);
	}

	////////// calculate test ants ///////////////////////////////
	// in order to see them, also uncomment the test variables in Ant_Sim.h and 
	// in the constructor, uncomment in Ant_Sim.start() clean_up_test_ants(); 
	// in Ant_Sim.game_logic move_test_ants and in Drawing_engine.draw_ants
	//
	//for (int cnt = 0; cnt < _ant_number; cnt++)
	//{
	//	_ant_posx[cnt] = rand() % (BOARD_SIZE-40) + 20;
	//	_ant_posz[cnt] = rand() % (BOARD_SIZE-40) + 20;
	//}
	//////////////////////////////////////////////////////////////
}


////////// calculate test ants ///////////////////////////////
// in order to see them, also uncomment the test variables in Ant_Sim.h and
// in the constructor, the block in the Ant_Sim.init()
// uncomment also in Ant_Sim.start() clean_up_test_ants(); 
// in Ant_Sim.game_logic move_test_ants and in Drawing_engine.draw_ants
//////////////////////////////////////////////////////////////

//void Ant_Sim::move_test_ants(void)
//{
//	int velocity = (_round_cnt%360)/45;	 
//	switch(velocity) {
//	case 0:
//		for (int cnt = 0; cnt < _ant_number; cnt++) {_ant_posz[cnt] += 1;}
//		break;
//	case 2:
//		for (int cnt = 0; cnt < _ant_number; cnt++) {_ant_posx[cnt] += 1;}
//		break;
//	case 4:
//		for (int cnt = 0; cnt < _ant_number; cnt++) {_ant_posz[cnt] -= 1;}
//		break;
//	case 6:
//		for (int cnt = 0; cnt < _ant_number; cnt++) {_ant_posx[cnt] -= 1;}
//		break;
//	default:
//		_ant_angley += 90/45; break;
//	}
//}


//void Ant_Sim::clean_up_test_ants(void)
//{
//	delete(_ant_posx);
//	delete(_ant_posz);
//}

int Ant_Sim::read_play_time_from_file(std::string file)
{
	std::vector<std::string> lines;
	std::ifstream fin(file);
	std::string line;
	while( std::getline(fin, line) )
	{
		lines.push_back(line);
	}
	double play_time = atof(lines[16].c_str());
	return play_time;
}

void Ant_Sim::handle_user_input(SDL_Event &event)
{
	switch(event.type) {
		case SDL_QUIT:
			if (_countdown_on)	{ _running = false; }
			else				{ start_countdown(); }
			break;
		case SDL_MOUSEBUTTONDOWN:
			// left mouse click
			if (event.button.button ==SDL_BUTTON_LEFT)
				{ _drawing_engine.left_mouse_click(); break; } 
		case SDL_MOUSEBUTTONUP:
				{ _drawing_engine.left_mouse_unclick(); break; } 
		case SDL_KEYUP:
			switch(event.key.keysym.sym) {
				case SDLK_p:
					_drawing_engine.print_cam_pos(); break;
				case SDLK_f:
					_drawing_engine.switch_fog_no_fog(); break;	
				case SDLK_q:
					_drawing_engine.switch_good_bad_graphics(); break;	
				case SDLK_n:
					_sim_time_step = std::min<int>(_sim_time_step+1,300); break;						
				case SDLK_m:
					_sim_time_step = std::max<int>(_sim_time_step-1,2); break;
				case SDLK_ESCAPE:
					if (_countdown_on)	{ _running = false; }
					else				{ start_countdown(); }
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void Ant_Sim::start_countdown(void)
{
	_countdown_on = true;
	_drawing_engine.start_countdown();
	_time_remaining = 10000;
}

void Ant_Sim::game_logic(Uint32 time)
{
	_round_cnt++;
	//move_test_ants();

	if (!_is_replay)
	{
		_table_items->update_passive(time, _sim_time_step);
		_coll_dect->update_all(time, _sim_time_step);
	}

	// check if game time is over
	_time_remaining -= _sim_time_step;
	if (_time_remaining <= 0)
	{
		if (!_countdown_on)
			// game run out of time -> start countdown and show results
			start_countdown();
		else
			// countdown is already over -> finish the simulation
			_running = false;
	}
}

void Ant_Sim::add_colony(void)
{
	Colony_birth_info colony_birth_info;
	colony_birth_info._size = 100;
	colony_birth_info.read_from_file(FILE_NAME);
	auto new_colony_ptr = std::make_shared<Colony>(colony_birth_info);
	(*_table_items).add_colony(new_colony_ptr);
}

void Ant_Sim::add_food(double amount, int x, int y, int z)
{
	Game_item_birth_info go_info;
	go_info._energy = amount;
	go_info._size = amount;
	go_info._energy_consumption_per_m = 0;
	std::array<double, 2> dir = {1.0, 0.0};
	Position pos(x,y,z,dir);
	go_info._pos = pos;
	auto new_food_ptr = std::make_shared<Food>(go_info);
	(*_table_items).add_food(new_food_ptr);
}

void Ant_Sim::add_start_food(int number_of_items)
{
	for (int cnt = 0; cnt < number_of_items; cnt++)
	{
		double x = unif_01() * (BOARD_SIZE-400) + 200;
		double z = unif_01() * (BOARD_SIZE-400) + 200;
		double amount = std::max<double>(unif_01()*200,10);
		add_food(amount,x,0,z);
	}
}

void Ant_Sim::add_obstacle(double size, int x, int y, int z)
{
	Game_item_birth_info go_info;
	go_info._energy = size;
	go_info._size = size;
	go_info._energy_consumption_per_m = 0;
	std::array<double, 2> dir = {1.0, 0.0};
	Position pos(x,y,z,dir);
	go_info._pos = pos;
	auto new_obst_ptr = std::make_shared<Obstacle>(go_info);
	(*_table_items).add_obstacle(new_obst_ptr);
}

void Ant_Sim::start(void)
{
	_drawing_engine.init();
	init();

	// set local variables
	SDL_Event event;
	Time_machine time_machine; // to keep control of time flux
	Uint32 time = 0; // in milli seconds
	Uint32 accumulator = 0;

	while(_running) {
		////////////////////////////////////////////////////////
		/////////////         EVENT HANDLING      //////////////
		////////////////////////////////////////////////////////
		while(SDL_PollEvent(&event))
		{
			handle_user_input(event);
		}
		////////////////////////////////////////////////////////
		/////////////            GAME LOGIC       //////////////
		////////////////////////////////////////////////////////
		accumulator += time_machine.return_frame_time();
		time_machine.print_time_status(_round_cnt, _sim_time_step);

		while ( accumulator >= _sim_time_step )
		{
			game_logic(time);

			// operations to hold constant time flux
			accumulator -= _sim_time_step;
			time += _sim_time_step;
		}
		////////////////////////////////////////////////////////
		/////////////        GRAPHIC RENDERING    //////////////
		////////////////////////////////////////////////////////
		_drawing_engine.display(this, _time_remaining, _round_cnt);
		SDL_GL_SwapBuffers(); // blits the buffer to the screen
	}
	_drawing_engine.clean_up();
	//clean_up_test_ants();
	SDL_Quit();
}

void Ant_Sim::start_text_output(std::string input_file)
{ // save simulation to text_file
	init();

	// set local variables
	Uint32 time = 0; // in milli seconds

	save_time_step();
	save_obstacles();
	save_colonies();

	while(_running) {
		// SAVING TO TEXTFILE
		save_hud();
		save_ants();
		if (_round_cnt%100 == 0) save_food();

		// GAME LOGIC
		game_logic(time);
		time += _sim_time_step;
		if (_round_cnt % 1000 == 0) {
			int minutes = _time_remaining/60000;
			int seconds = (_time_remaining%60000)/1000;
			std::cout << "Remaining: " << minutes << " min " << seconds << std::endl;
		}
		if (_time_remaining <= 0) _running = false;
	}
	write_to_file(input_file);
}

void Ant_Sim::start_text_input(std::string input_file)
{
	_drawing_engine.init();
	init();
	_is_replay = true;

	// set local variables
	SDL_Event event;
	Time_machine time_machine; // to keep control of time flux
	Uint32 time = 0; // in milli seconds
	Uint32 accumulator = 0;

	// loading methods
	load_text_file(input_file);
	load_time_step();
	load_obstacles();
	load_colony();
	std::cout << std::endl << "Press ENTER to start Simulation. ";
	std::cin.ignore();

	while(_running) {
		////////////////////////////////////////////////////////
		/////////////         EVENT HANDLING      //////////////
		////////////////////////////////////////////////////////
		while(SDL_PollEvent(&event))
		{
			handle_user_input(event);
		}
		////////////////////////////////////////////////////////
		/////////////            GAME LOGIC       //////////////
		////////////////////////////////////////////////////////
		accumulator += time_machine.return_frame_time();
		time_machine.print_time_status(_round_cnt, _sim_time_step);

		while ( accumulator >= _sim_time_step )
		{
			if (!_save_game_list.empty())
			{
				load_hud();
				load_ants();
				if (_round_cnt%100 == 0) load_food();
			}
			game_logic(time);

			// operations to hold constant time flux
			accumulator -= _sim_time_step;
			time += _sim_time_step;
		}
		////////////////////////////////////////////////////////
		/////////////        GRAPHIC RENDERING    //////////////
		////////////////////////////////////////////////////////
		_drawing_engine.display(this, _time_remaining, _round_cnt);
		SDL_GL_SwapBuffers(); // blits the buffer to the screen
	}
	_drawing_engine.clean_up();
	
	// clean up
	for (std::list<std::list<float>>::iterator it = _save_game_list.begin() ; 
		it != _save_game_list.end(); ++it)
	{
		(*it).clear();
	}

	SDL_Quit();
}

void Ant_Sim::save_time_step(void)
{
	std::list<float> time_step_list;
	time_step_list.push_back(_sim_time_step);
	_save_game_list.push_back(time_step_list);
}

void Ant_Sim::save_hud(void)
{
	std::list<float> hud_list;
	hud_list.push_back(_time_remaining);
	std::shared_ptr<Colony> my_colony = _table_items->_colony_list.front();
	hud_list.push_back(my_colony->get_number_of_larvas());
	hud_list.push_back(_table_items->_ant_list.size());
	hud_list.push_back(my_colony->get_queen_hp());
	double solid_food_rounded = std::floor(100*(my_colony->get_solid_food()))/100.0;
	double liquid_food_rounded = std::floor(100*(my_colony->get_liquid_food()))/100.0;
	hud_list.push_back(solid_food_rounded);
	hud_list.push_back(liquid_food_rounded);
	_save_game_list.push_back(hud_list);
}

void Ant_Sim::save_ants(void)
{
	std::list<float> ant_list;
	for (std::list<std::shared_ptr<Ant>>::iterator ant_it = _table_items->_ant_list.begin(); 
		ant_it != _table_items->_ant_list.end() ; ++ant_it)
	{ 
		ant_list.push_back((*ant_it)->_pos._x);
		ant_list.push_back((*ant_it)->_pos._z);
		double ant_angle_rad = M_PI;
		if ((*ant_it)->_pos._direction[1] != -1)
			ant_angle_rad = 2*atan((*ant_it)->_pos._direction[0]/(1+(*ant_it)->_pos._direction[1]));
		double ant_angle_deg = 180 + ant_angle_rad * 180 / M_PI;
		ant_list.push_back(ant_angle_deg);
	}
	_save_game_list.push_back(ant_list);	
}

void Ant_Sim::save_colonies(void)
{
	std::list<float> colony_list;
	for (std::list<std::shared_ptr<Colony>>::iterator colony_it = _table_items->_colony_list.begin(); 
		colony_it != _table_items->_colony_list.end() ; ++colony_it)
	{ 
		colony_list.push_back((*colony_it)->_pos._x);
		colony_list.push_back((*colony_it)->_pos._z);
		colony_list.push_back((*colony_it)->get_size());
	}
	_save_game_list.push_back(colony_list);
}

void Ant_Sim::save_food(void)
{
	std::list<float> food_list;
	for (std::list<std::shared_ptr<Food>>::iterator food_it = _table_items->_food_list.begin(); 
		food_it != _table_items->_food_list.end() ; ++food_it)
	{ 
		food_list.push_back((*food_it)->_pos._x);
		food_list.push_back((*food_it)->_pos._z);
		food_list.push_back((*food_it)->get_size());
	}
	_save_game_list.push_back(food_list);
}

void Ant_Sim::save_obstacles(void)
{
	std::list<float> obstacle_list;
	for (std::list<std::shared_ptr<Obstacle>>::iterator obstacle_it = _table_items->_obstacle_list.begin(); 
		obstacle_it != _table_items->_obstacle_list.end() ; ++obstacle_it)
	{ 
		obstacle_list.push_back((*obstacle_it)->_pos._x);
		obstacle_list.push_back((*obstacle_it)->_pos._z);
		obstacle_list.push_back((*obstacle_it)->get_size());
	}
	_save_game_list.push_back(obstacle_list);
}

void Ant_Sim::write_to_file(std::string output_file)
{
	std::ofstream save_game;
	save_game.open (output_file);

	for (std::list<std::list<float>>::iterator line_ptr = _save_game_list.begin(); 
			line_ptr != _save_game_list.end(); ++line_ptr)
	{
		std::stringstream sstm;
		for (std::list<float>::iterator entry_ptr = (*line_ptr).begin(); 
		entry_ptr != (*line_ptr).end(); ++entry_ptr)
		{
			sstm << (*entry_ptr) << " ";
		}
		sstm << "\n";
		std::string new_line = sstm.str();
		save_game << new_line;
	}

	save_game.close();
}

void Ant_Sim::load_text_file(std::string input_file)
{
	std::ifstream fin(input_file);
	std::string line;
	while( std::getline(fin, line))
	{
		std::vector<std::string> line_vec = split(line, ' ');
		std::list<float> temp_list;
		for (std::vector<std::string>::iterator it = line_vec.begin() ; it != line_vec.end(); ++it)
		{
			if ((*it).size() != 0)
			{
				float recent_number = atof((*it).c_str());
				temp_list.push_back(recent_number);
			}
		}
		_save_game_list.push_back(temp_list);
	}
}

std::vector<std::string> Ant_Sim::split(std::string s, char delim) 
{
	std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void Ant_Sim::load_time_step(void)
{
	_sim_time_step = (_save_game_list.front()).front();
	_save_game_list.pop_front();
}

void Ant_Sim::load_obstacles(void)
{
	_obstacle_list = _save_game_list.front();
	_save_game_list.pop_front();
}

void Ant_Sim::load_colony(void)
{
	_colony_list = _save_game_list.front();
	_save_game_list.pop_front();
}

void Ant_Sim::load_hud(void)
{
	_hud_list = _save_game_list.front();
	_save_game_list.pop_front();
}

void Ant_Sim::load_ants(void)
{
	_ant_list = _save_game_list.front();
	_save_game_list.pop_front();
}

void Ant_Sim::load_food(void)
{
	_food_list = _save_game_list.front();
	_save_game_list.pop_front();
}