#include "Ant_Sim.h"

Ant_Sim::Ant_Sim(int ant_number, int FPS, int cam_velocity)
{
	_ant_number = ant_number;
	_FPS = FPS;
	_cam_velocity = cam_velocity;
	_switch_fog_on = false;
	_high_quality_on = false;
	_ant_posx = new float[_ant_number];
	_ant_posz = new float[_ant_number];

	// system variables
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
	SDL_WM_SetCaption( "Ant Simulation", NULL );
	Uint32 colorkey;
	SDL_Surface *icon;
	icon = SDL_LoadBMP("src/icon.bmp");
	colorkey = SDL_MapRGB(icon->format, 111,111,111);
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

	int recent_cam_velocity = 1;
	if(_keystates[SDLK_LSHIFT])
		recent_cam_velocity *= 4;
	camera_control(recent_cam_velocity,0.5,board_size,screen_width,screen_height,_mousein);
	draw_skybox(SKY_BOY_DISTANCE); // don't make it bigger than the far-view-plane (see gluPerspective)
	update_camera();
	draw_board(board_size, _tex_board);
	draw_border(board_size, _tex_border);

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

void Ant_Sim::start(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	// SDL_SWSURFACE|SDL_OPENGL means: do both options
	_prescreen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE);
	//screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE|SDL_FULLSCREEN);
	SDL_Surface *logo = load_image("src/logo.png");
	//SDL_BlitSurface( hello, NULL, screen, NULL ); 
	apply_surface( 200, 150, logo, _prescreen );
	SDL_Flip( _prescreen ); 
	_screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE|SDL_OPENGL);
	bool running = true;
	Uint32 time = 0;
	Uint32 time_step = 10; // in milli seconds
	Uint32 current_time = SDL_GetTicks();
	Uint32 accumulator = 0;
	Uint32 time_stopper = 0;
	int round_cnt_save = 0;
	int frame_cnt_save = 0;
	int frame_cnt = 0;

	SDL_Event event;
	init();

	AnimMesh *ant=new AnimMesh(16,"src/fourmi_obj/fourmi2"); //On charge les frames
    VirtualAnim *anim=new VirtualAnim(); //We create a virtual animation
 
    anim->start(0,15,50); //On lance l'animation

	while(running) {
		////////////////////////////////////////////////////////
		/////////////         EVENT HANDLING      //////////////
		////////////////////////////////////////////////////////
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running = false; break;
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
							time_step = min(time_step+1,300); break;						
						case SDLK_m:
							time_step = max(time_step-1,2); break;
						case SDLK_ESCAPE:
							running = false; break;
						default:
							break;
				    }
					break;
				default:
					break;
			}
		}
		Uint32 new_time = SDL_GetTicks();
		Uint32 frame_time = new_time - current_time;
		current_time = new_time;
		accumulator += frame_time;
		// calculate and print frame rate
		if (new_time-time_stopper  > 3000) {
			float rounds = (_round_cnt-round_cnt_save) / ( (new_time-time_stopper) / 1000.f );
			cout << "Rounds per realtime sec: " << rounds
			     << " = " << time_step * rounds / 1000
				 << " simulation sec by " << (frame_cnt-frame_cnt_save) / ( (new_time-time_stopper) / 1000.f )
				 << " FPS."<< endl;
			time_stopper = new_time;
			round_cnt_save = _round_cnt;
			frame_cnt_save = frame_cnt;
		}

		////////////////////////////////////////////////////////
		/////////////            GAME LOGIC       //////////////
		////////////////////////////////////////////////////////
		while ( accumulator >= time_step )
		{
			_round_cnt++;
			move_ants();

			// operations to hold constant time flux
			accumulator -= time_step;
			time += time_step;
		}
		frame_cnt++;
		////////////////////////////////////////////////////////
		/////////////        GRAPHIC RENDERING    //////////////
		////////////////////////////////////////////////////////
		display(anim,ant);
		SDL_GL_SwapBuffers(); // blits the buffer to the screen
		
	}
	SDL_FreeSurface( _prescreen );
	SDL_FreeSurface( _screen );
	SDL_FreeSurface( logo );
	SDL_Quit();
	kill_skybox();
	glDeleteTextures(1,&_tex_board);
	glDeleteTextures(1,&_tex_border);
	delete(_ant_posx);
	delete(_ant_posz);

	delete anim;
    delete ant;
}