#include "Ant_Sim.h"

Ant_Sim::Ant_Sim(int ant_number, int play_time)
{
	_ant_number = ant_number;
	_time_remaining = play_time*1000;
	_sim_time_step = 10; // in milli seconds
	_cam_velocity = 2;
	_max_size_of_pheromone = 300;

	// boolean checks
	_running = true;
	_mousein = false;
	_countdown_on = false;
	_high_quality_on = false;
	_switch_fog_on = false;

	// graphic related variables
	_recent_cam_velocity = _cam_velocity;
	_round_cnt = 0;
	_keystates = SDL_GetKeyState( NULL );
	_ant_posx = new float[_ant_number];
	_ant_posz = new float[_ant_number];

	// just for testing / not important
	_ant_posy = 2;
	_ant_size = 10;
	_ant_angley = 180;
}

Ant_Sim::~Ant_Sim(void)
{
}

void Ant_Sim::move_ants(void)
{
	int velocity = (_round_cnt%360)/45;	 
	switch(velocity) {
	case 0:
		for (int cnt = 0; cnt < _ant_number; cnt++) {_ant_posz[cnt] += 1;}
		break;
	case 2:
		for (int cnt = 0; cnt < _ant_number; cnt++) {_ant_posx[cnt] += 1;}
		break;
	case 4:
		for (int cnt = 0; cnt < _ant_number; cnt++) {_ant_posz[cnt] -= 1;}
		break;
	case 6:
		for (int cnt = 0; cnt < _ant_number; cnt++) {_ant_posx[cnt] -= 1;}
		break;
	default:
		_ant_angley += 90/45; break;
	}
}

void Ant_Sim::set_window(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// create prescreen to show logo while everything is initialized
	_prescreen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE);
	_logo = load_image("src/logo.png");
	apply_surface( 200, 150, _logo, _prescreen );
	SDL_Flip( _prescreen ); 

	// set up the real screen
	_screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE|SDL_OPENGL);
	// SDL_SWSURFACE|SDL_OPENGL means: do both options
	// for full screen:
	//screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE|SDL_FULLSCREEN);
	SDL_WM_SetCaption( "Ant Simulation", NULL );
	SDL_Surface *icon;
	icon = SDL_LoadBMP("src/icon.bmp");
	Uint32 colorkey = SDL_MapRGB(icon->format, 111,111,111);
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, colorkey);              
	SDL_WM_SetIcon(icon,NULL);
	SDL_FreeSurface(icon);
}

void Ant_Sim::set_openGL(void)
{
	glClearColor(0.2,0.2,0.8,1.0); //background color and alpha
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(1.0*screen_width)/screen_height,1.0,10000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//Initialize OpenGL
	//Texture mapping and blending must be enabled for glFont to work
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Ant_Sim::set_fog(void)
{
	if (_switch_fog_on) { glEnable(GL_FOG); }
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_START,800.0);
	glFogf(GL_FOG_END,3000.0);
	float fog_color[] = {0.7,0.7,.80,0.8};
	glFogfv(GL_FOG_COLOR,fog_color);
}

void Ant_Sim::load_textures(void)
{
	_tex_board=load_texture_png("src/grass.png", 512, 512, false, true);
	_tex_colony=load_texture_png("src/gravel.png", 256, 256, false, true);
	_tex_box=load_texture_png("src/box.png", 256, 256, false, true);
	_tex_apple_side=load_texture_png("src/apple_side.png", 256, 256, false, true);
	_tex_apple_top=load_texture_png("src/apple_top.png", 256, 256, false, true);
	_tex_border=load_texture_png("src/border.png", 1024, 1024);
	_tex_result=load_texture_png("src/result.png", 512, 512);
	_tex_result_pointer=load_texture_png("src/result_pointer.png", 128, 128);
}

void Ant_Sim::load_hq_ants(void)
{
	for (int i = 0; i <= 7; i++)
	{	
		std::stringstream sstm;
		sstm << "src/fourmi_obj/fourmi3_0000" << i << "1.obj";
		std::string file_name = sstm.str();
		_ant_hq_array[i] = new MeshObj(file_name);
	}
}

void Ant_Sim::init(void)
{
	set_window();
	set_openGL();
	// set glFont
	_screen_text.Create("src/didactgothic.glf", 1);
	set_fog();
	init_skybox();
	load_textures();

	// just for testing purposes, create random ants
	for (int cnt = 0; cnt < _ant_number; cnt++)
	{
		_ant_posx[cnt] = rand() % (board_size-40) + 20;
		_ant_posz[cnt] = rand() % (board_size-40) + 20;
	}
}

void Ant_Sim::draw_text(std::string text, float x, float y)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor3f(1.0F, 1.0F, 0.0F);
	_screen_text.Begin();
	_screen_text.DrawString(text, 1.5F, x, y);
    glDisable(GL_BLEND); 
}

void Ant_Sim::draw_text_with_number(std::string text, int number, float x, float y)
{
	std::stringstream sstm;
	sstm << text << number;
	std::string info_str = sstm.str();
	draw_text(info_str, x, y);
}

void Ant_Sim::draw_countdown(int time_remaining_in_s)
{
	int x_pos = (int)(screen_width/4);
	int y_pos = (int)(screen_height*7/8);
	std::stringstream sstm;
	sstm << "Time until shutdown: " << time_remaining_in_s;
	std::string time_remaing_str = sstm.str();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor3f(1.0F, 0.0F, 0.0F);
	_screen_text.Begin();
	_screen_text.DrawString(time_remaing_str, 2.5F, x_pos, y_pos);
    glDisable(GL_BLEND); 
}

void Ant_Sim::draw_hud(void)
{
	int time_remaining_in_s = (int)_time_remaining/1000;
	float x_coord = screen_width-320.0;
	float y_coord = screen_height-50.0;
	draw_text_with_number("Time remaining: ", time_remaining_in_s, x_coord, y_coord);

	if (_countdown_on) draw_countdown(time_remaining_in_s);
}


void Ant_Sim::draw_result(void)
{
	glPushMatrix();
		glTranslatef(400,0,400);
	
	glPopMatrix();
}

void Ant_Sim::switch_to_normal_perspective(int field_of_view_in_degrees)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(field_of_view_in_degrees,(1.0*screen_width)/screen_height,1.0,10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Ant_Sim::switch_to_ortho_perspective(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screen_width, 0, screen_height, -1, 8000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Ant_Sim::display(void)
{
	// in color_buffer the color of every pixel is saved
	// in depth buffer the depth of every pixel is saved (which px is in front of which)
	// usually, it makes sense to clean the buffers after every frame
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	switch_to_normal_perspective(45);
	if(_keystates[SDLK_LSHIFT]) { _recent_cam_velocity += 1; }
	else { _recent_cam_velocity = _cam_velocity; }
	_camera.control(_recent_cam_velocity,0.5,board_size,screen_width,screen_height,_mousein);
	// don't make it bigger than the far-view-plane (see gluPerspective)
	draw_skybox(SKY_BOY_DISTANCE); 
	_camera.update();
	draw_board(board_size, _tex_board);
	draw_border(board_size, _tex_border);

	// draw a colony
	glPushMatrix();
		glTranslatef(100,0,100);
		draw_colony(100, _tex_colony);
	glPopMatrix();

	// draw a box
	glPushMatrix();
		glTranslatef(100,0,300);
		draw_box(70, _tex_box, _tex_box);
	glPopMatrix();

	// draw an apple
	glPushMatrix();
		glTranslatef(400,0,400);
		draw_box(100, _tex_apple_side, _tex_apple_top);
	glPopMatrix();
	
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3))
	// right mouse click
	{
		std::vector<double> pos_on_board = _camera.calculate_click_point(board_size);
		glPushMatrix();
			glTranslatef(pos_on_board[0],2,pos_on_board[1]);
			draw_pic(100, _tex_apple_top);
		glPopMatrix();
	}
	
	//for low quality ants
	double ant_color[3] =  {0.2, 0.0, 0.0};
	int freq = 50;
	double anim_frame = std::abs((_round_cnt%freq)/(0.25*freq)-2)-1;

	//for high quality ants
	int hq_frame = (_round_cnt%40)/5;

	for (int cnt = 0; cnt < _ant_number; cnt++) 
	{
		glPushMatrix();
			glTranslatef(_ant_posx[cnt],_ant_posy,_ant_posz[cnt]);
			glRotatef(_ant_angley,0.0,1.0,0.0);
			if (_high_quality_on) { _ant_hq_array[hq_frame]->draw_model(); }
			else { draw_ant_anim(_ant_size, ant_color, anim_frame); }
		glPopMatrix();
	}

	glPushMatrix();
		switch_to_ortho_perspective();
		draw_hud();
	glPopMatrix();
	glFlush();
}

void Ant_Sim::clean_up(void)
{
	SDL_FreeSurface( _prescreen );
	SDL_FreeSurface( _screen );
	SDL_FreeSurface( _logo );
	kill_skybox();
	glDeleteTextures(1,&_tex_board);
	glDeleteTextures(1,&_tex_border);
	delete(_ant_posx);
	delete(_ant_posz);
	for (int i = 0; i <= 7; i++)
	{
		delete(_ant_hq_array[i]);
	}
}

void Ant_Sim::handle_user_input(SDL_Event &event)
{
	switch(event.type) {
		case SDL_QUIT:
			if (!_countdown_on) 
				start_countdown(); 
			break;
		case SDL_MOUSEBUTTONDOWN:
			// left mouse click
			if (event.button.button ==SDL_BUTTON_LEFT)
			{
				_mousein = true;
				SDL_ShowCursor(SDL_DISABLE);
				SDL_WarpMouse(screen_width/2,screen_height/2);
				break;
			} 
		case SDL_MOUSEBUTTONUP:
			_mousein = false;
			SDL_ShowCursor(SDL_ENABLE);
			break;
		case SDL_KEYUP:
			switch(event.key.keysym.sym) {
				case SDLK_p:
					_camera.print(); break;
				case SDLK_f:
					_switch_fog_on= !_switch_fog_on;
					if (_switch_fog_on) { glEnable(GL_FOG); }
					else {glDisable(GL_FOG); }
					break;	
				case SDLK_q:
					_high_quality_on = !_high_quality_on; break;	
				case SDLK_n:
					_sim_time_step = std::min<int>(_sim_time_step+1,300); break;						
				case SDLK_m:
					_sim_time_step = std::max<int>(_sim_time_step-1,2); break;
				case SDLK_ESCAPE:
					if (!_countdown_on) 
						start_countdown(); 
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void Ant_Sim::start(void)
{
	init();
	load_hq_ants();

	// set local variables
	SDL_Event event;
	Time_machine time_machine; // to keep control of time flux
	Uint32 time = 0; // in milli seconds
	Uint32 accumulator = 0;
		  
	auto table_obj = std::make_shared<Table_of_objects>(2500, board_size);
	auto coll_dect = std::make_shared<Collision_detector>(table_obj, 
							_max_size_of_pheromone, _max_size_of_vision, _max_size_of_corps);

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
			_round_cnt++;
			move_ants();

			//table_obj->update_passive(time, _sim_time_step);
			//coll_dect->update_active(time, _sim_time_step);

			// check if game time is over
			_time_remaining -= _sim_time_step;
			if (_time_remaining <= 0)
				if (!_countdown_on)
					// game run out of time -> start countdown and show results
					start_countdown();
				else
					// countdown is already over -> finish the simulation
					_running = false;

			// operations to hold constant time flux
			accumulator -= _sim_time_step;
			time += _sim_time_step;
		}
		////////////////////////////////////////////////////////
		/////////////        GRAPHIC RENDERING    //////////////
		////////////////////////////////////////////////////////
		display();
		SDL_GL_SwapBuffers(); // blits the buffer to the screen
	}
	clean_up();
	SDL_Quit();
}

void Ant_Sim::start_countdown(void)
{
	_countdown_on = true;
	_time_remaining = 3000;
}