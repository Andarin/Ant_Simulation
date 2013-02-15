#include "Ant_Sim.h"

Ant_Sim::Ant_Sim(int ant_number, int FPS, int cam_velocity)
{
	_ant_number = ant_number;
	_FPS = FPS;
	_sim_time_step = 10; // in milli seconds
	_cam_velocity = cam_velocity;
	_recent_cam_velocity = _cam_velocity;
	_switch_fog_on = false;
	_high_quality_on = false;
	_ant_posx = new float[_ant_number];
	_ant_posz = new float[_ant_number];

	// system variables
	_running = true;
	_round_cnt = 0;
	_mousein = false;
	_keystates = SDL_GetKeyState( NULL );

	// just for testing / not important
	_ant_posy = 2;
	_ant_size = 10;
	_ant_angley = 180;
}

Ant_Sim::~Ant_Sim(void)
{
}

void Ant_Sim::move_ants()
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

void Ant_Sim::set_openGL()
{
	glClearColor(0.2,0.2,0.8,1.0); //background color and alpha
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(1.0*screen_width)/screen_height,1.0,10000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void Ant_Sim::set_fog(void)
{
	if (_switch_fog_on) { glEnable(GL_FOG); }
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_START,800.0);
	glFogf(GL_FOG_END,3000.0);
	float fog_color[] = {0.33,0.5,.80,0.7};
	glFogfv(GL_FOG_COLOR,fog_color);
}

void Ant_Sim::init()
{
	set_window();
	set_openGL();
	set_fog();
	init_skybox();
	_tex_board=load_texture_png("src/grass.png", 512, 512, false, true);
	_tex_colony=load_texture_png("src/gravel.png", 256, 256, false, true);
	_tex_box=load_texture_png("src/box.png", 256, 256, false, true);
	_tex_apple_side=load_texture_png("src/apple_side.png", 256, 256, false, true);
	_tex_apple_top=load_texture_png("src/apple_top.png", 256, 256, false, true);
	_tex_border=load_texture_png("src/border.png", 1024, 1024);
	for (int cnt = 0; cnt < _ant_number; cnt++)
	{
		_ant_posx[cnt] = rand() % (board_size-40) + 20;
		_ant_posz[cnt] = rand() % (board_size-40) + 20;
	}
}

void Ant_Sim::display(VirtualAnim *anim, AnimMesh *fish)
{
	// in color_buffer the color of every pixel is saved
	// in depth buffer the depth of every pixel is saved (which px is in front of which)
	// usually, it makes sense to clean the buffers after every frame
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(_keystates[SDLK_LSHIFT]) { _recent_cam_velocity += 1; }
	else { _recent_cam_velocity = _cam_velocity; }
	camera_control(_recent_cam_velocity,0.5,board_size,screen_width,screen_height,_mousein);
	draw_skybox(SKY_BOY_DISTANCE); // don't make it bigger than the far-view-plane (see gluPerspective)
	update_camera();
	draw_board(board_size, _tex_board);
	draw_border(board_size, _tex_border);

	// draw a colony
	glPushMatrix();
		glTranslatef(100,0,100);
		draw_colony(100, _tex_colony);
	glPopMatrix();

	// draw a box
	glPushMatrix();
		glTranslatef(220,0,220);
		draw_box(70, _tex_box, _tex_box);
	glPopMatrix();

	// draw an apple
	glPushMatrix();
		glTranslatef(400,0,400);
		draw_box(100, _tex_apple_side, _tex_apple_top);
	glPopMatrix();

	glCallList(_ant_model);
	for (int cnt = 0; cnt < _ant_number; cnt++) 
	{
		glPushMatrix();
			glTranslatef(_ant_posx[cnt],_ant_posy,_ant_posz[cnt]);
			glRotatef(_ant_angley,0.0,1.0,0.0);
			if (_high_quality_on) { anim->draw(fish,false,true); }
			else { draw_ant(_ant_size); }
			//
		glPopMatrix();
	}
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

	SDL_Quit();
}

void Ant_Sim::handle_user_input(SDL_Event &event)
{
	switch(event.type) {
		case SDL_QUIT:
			_running = false; break;
		case SDL_MOUSEBUTTONDOWN:
			_mousein = true;
			SDL_ShowCursor(SDL_DISABLE);
			SDL_WarpMouse(screen_width/2,screen_height/2);
			break;
		case SDL_MOUSEBUTTONUP:
			_mousein = false;
			SDL_ShowCursor(SDL_ENABLE);
			break;
		case SDL_KEYUP:
			switch(event.key.keysym.sym) {
				case SDLK_p:
					print_camera_pos(); break;
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
					_running = false; break;
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

	// set local variables
	SDL_Event event;
	Time_machine time_machine; // to keep control of time flux
	Uint32 time = 0; // in milli seconds
	Uint32 accumulator = 0;

	// better graphics meshes
	AnimMesh *ant=new AnimMesh(16,"src/fourmi_obj/fourmi2"); //On charge les frames
    VirtualAnim *anim=new VirtualAnim(); //We create a virtual animation
    anim->start(0,15,50); // we start the animation

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
			// operations to hold constant time flux
			accumulator -= _sim_time_step;
			time += _sim_time_step;
		}
		////////////////////////////////////////////////////////
		/////////////        GRAPHIC RENDERING    //////////////
		////////////////////////////////////////////////////////
		display(anim, ant);
		SDL_GL_SwapBuffers(); // blits the buffer to the screen
	}
	delete anim;
    delete ant;
	clean_up();
}