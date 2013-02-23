// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Ant_Sim.h"

Ant_Sim::Ant_Sim(void)
{
	_time_remaining = read_play_time_from_file(FILE_NAME)*1000;
	_sim_time_step = 20; // in milli seconds
	_max_size_of_pheromone = 300;
	_max_size_of_corps = 100;

	// boolean checks
	_running = true;
	_countdown_on = false;

	// graphic related variables
	_round_cnt = 0;
	_keystates = SDL_GetKeyState( NULL );

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

	add_colony();
	add_start_food(50);
	add_obstacle(150,BOARD_SIZE-200,0,BOARD_SIZE-200);
	add_obstacle(100,BOARD_SIZE-200,0,BOARD_SIZE-300);
	add_obstacle(50,BOARD_SIZE-300,0,BOARD_SIZE-300);

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

	_table_items->update_passive(time, _sim_time_step);
	_coll_dect->update_all(time, _sim_time_step);

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
