#include "Drawing_engine.h"
#include "Ant_Sim.h"

Drawing_engine::Drawing_engine(void)
{
	// graphic related variables
	_cam_velocity = 2;
	_recent_cam_velocity = _cam_velocity;
	_keystates = SDL_GetKeyState( NULL );

	// boolean checks
	_mousein = false;
	_countdown_on = false;
	_high_quality_on = false;
	_switch_fog_on = false;
	_building_menu_on = false;
}

Drawing_engine::~Drawing_engine(void)
{
}

void Drawing_engine::set_window(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// create prescreen to show logo while everything is initialized
	_prescreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
	_logo = load_image("src/logo.png");
	apply_surface( 200, 150, _logo, _prescreen );
	SDL_Flip( _prescreen ); 

	// set up the real screen
	_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE|SDL_OPENGL);
	// SDL_SWSURFACE|SDL_OPENGL means: do both options
	// for full screen:
	//screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE|SDL_FULLSCREEN);
	SDL_WM_SetCaption( "Ant Simulation", NULL );
	SDL_Surface *icon;
	icon = SDL_LoadBMP("src/icon.bmp");
	Uint32 colorkey = SDL_MapRGB(icon->format, 111,111,111);
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, colorkey);              
	SDL_WM_SetIcon(icon,NULL);
	SDL_FreeSurface(icon);
}

void Drawing_engine::set_openGL(void)
{
	glClearColor(0.2,0.2,0.8,1.0); //background color and alpha
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(1.0*SCREEN_WIDTH)/SCREEN_HEIGHT,1.0,10000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//Initialize OpenGL
	//Texture mapping and blending must be enabled for glFont to work
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Drawing_engine::init_fog(void)
{
	if (_switch_fog_on) { glEnable(GL_FOG); }
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_START,800.0);
	glFogf(GL_FOG_END,3000.0);
	float fog_color[] = {0.7,0.7,.80,0.8};
	glFogfv(GL_FOG_COLOR,fog_color);
}

void Drawing_engine::load_textures(void)
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

void Drawing_engine::load_hq_models(void)
{
	for (int i = 0; i <= 7; i++)
	{	
		std::stringstream sstm;
		sstm << "src/fourmi_obj/fourmi3_0000" << i << "1.obj";
		std::string file_name = sstm.str();
		_ant_hq_array[i] = new MeshObj(file_name);
	}

	_apple_hq = new MeshObj("src/apple/apple.obj");
}

void Drawing_engine::init(void)
{
	set_window();
	set_openGL();
	// set glFont
	_screen_text.Create("src/didactgothic.glf", 1);
	init_fog();
	init_skybox();
	load_textures();
	load_hq_models();
}

void Drawing_engine::draw_text(std::string text, float x, float y)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor3f(1.0F, 1.0F, 0.0F);
	_screen_text.Begin();
	_screen_text.DrawString(text, 1.2F, x, y);
    glDisable(GL_BLEND); 
}

void Drawing_engine::draw_text_with_number(std::string text, int number, float x, float y)
{
	std::stringstream sstm;
	sstm << text << number;
	std::string info_str = sstm.str();
	draw_text(info_str, x, y);
}

void Drawing_engine::draw_text_with_number(std::string text, double number, float x, float y)
{
	std::stringstream sstm;
	sstm << text << number;
	std::string info_str = sstm.str();
	draw_text(info_str, x, y);
}

void Drawing_engine::draw_countdown(int time_remaining_in_s)
{
	int x_pos = (int)(SCREEN_WIDTH/6);
	int y_pos = (int)(SCREEN_HEIGHT*7/8);
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

void Drawing_engine::draw_hud(Uint32 time_remaining, Ant_Sim *ant_sim_ptr)
{
	int larva_number = 0;
	int ant_number = (*ant_sim_ptr)._table_items->_ant_list.size();
	int queen_hp = 0;
	double liquid_food = 0;
	double solid_food = 0;
	std::list<std::shared_ptr<Colony>> colony_list = (*ant_sim_ptr)._table_items->_colony_list;
	for (std::list<std::shared_ptr<Colony>>::iterator col_it = colony_list.begin(); 
			col_it != colony_list.end() ; ++col_it)
		{ 
			// 0 is the "color" of the player
			if ((*col_it)->_color == 0)
			{
				larva_number += (*col_it)->get_number_of_larvas();
				queen_hp += (*col_it)->get_queen_hp();
				liquid_food += (*col_it)->get_liquid_food();
				solid_food += (*col_it)->get_solid_food();
			}
		}

	int time_remaining_in_s = (int)time_remaining/1000;

	float x_coord = SCREEN_WIDTH-250.0;
	float line_distance = 30;
	float y_coord = SCREEN_HEIGHT-20.0;
	draw_text_with_number("Time remaining: ", time_remaining_in_s, x_coord, y_coord);
	y_coord -= line_distance;
	draw_text_with_number("Larvas: ", larva_number, x_coord, y_coord);
	y_coord -= line_distance;
	draw_text_with_number("Ants: ", ant_number, x_coord, y_coord);
	y_coord -= line_distance;
	draw_text_with_number("Queen HP: ", queen_hp, x_coord, y_coord);
	y_coord -= line_distance;
	double solid_food_rounded = std::floor(100*solid_food)/100.0;
	double liquid_food_rounded = std::floor(100*liquid_food)/100.0;
	draw_text_with_number("Solid Food: ", solid_food, x_coord, y_coord);
	y_coord -= line_distance;
	draw_text_with_number("Liquid Food: ", liquid_food_rounded, x_coord, y_coord);
	
	if (_countdown_on) draw_countdown(time_remaining_in_s);
}

double Drawing_engine::calc_result(Ant_Sim *ant_sim_ptr)
{
	double liquid_food = 0;
	double solid_food = 0;
	std::list<std::shared_ptr<Colony>> colony_list = (*ant_sim_ptr)._table_items->_colony_list;
	for (std::list<std::shared_ptr<Colony>>::iterator col_it = colony_list.begin(); 
			col_it != colony_list.end() ; ++col_it)
	{ 
		// 0 is the "color" of the player
		if ((*col_it)->_color == 0)
		{
			liquid_food += (*col_it)->get_liquid_food();
			solid_food += (*col_it)->get_solid_food();
		}
	}
	return std::min<double>((liquid_food + solid_food)/1000.0,1.0);
}

void Drawing_engine::switch_to_normal_perspective(int field_of_view_in_degrees)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(field_of_view_in_degrees,(1.0*SCREEN_WIDTH)/SCREEN_HEIGHT,1.0,10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Drawing_engine::switch_to_ortho_perspective(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 8000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Drawing_engine::draw_foods(Ant_Sim* ant_sim_ptr)
{
	std::list<std::shared_ptr<Food>> food_list = (*ant_sim_ptr)._table_items->_food_list;
	for (std::list<std::shared_ptr<Food>>::iterator food_it = food_list.begin(); 
			food_it != food_list.end() ; ++food_it)
	{ 
		Position food_pos = (*food_it)->_pos;
		glPushMatrix();
			glTranslatef(food_pos._x,food_pos._y,food_pos._z);
			if (_high_quality_on) 
				{ _apple_hq->draw_model(); }
			else 
				{ draw_box((*food_it)->get_size(), _tex_apple_side, _tex_apple_top); }
		glPopMatrix();
	}

	//// draw a test apple
	//glPushMatrix();
	//glTranslatef(1000,0,1000);
	//if (_high_quality_on) { _apple_hq->draw_model(); }
	//else { draw_box(100, _tex_apple_side, _tex_apple_top); }
	//glPopMatrix();
}

void Drawing_engine::draw_obstacles(Ant_Sim* ant_sim_ptr)
{
	// draw a test box
	//glPushMatrix();
	//glTranslatef(100,0,300);
	//draw_box(70, _tex_box, _tex_box);
	//glPopMatrix();
}

void Drawing_engine::draw_colonies(Ant_Sim* ant_sim_ptr)
{
	std::list<std::shared_ptr<Colony>> colony_list = (*ant_sim_ptr)._table_items->_colony_list;
	for (std::list<std::shared_ptr<Colony>>::iterator col_it = colony_list.begin(); 
			col_it != colony_list.end() ; ++col_it)
	{ 
		Position col_pos = (*col_it)->_pos;
		glPushMatrix();
			glTranslatef(col_pos._x,col_pos._y,col_pos._z);
			draw_colony((*col_it)->get_size(), _tex_colony);
		glPopMatrix();
	}

	// draw a test colony
	//glPushMatrix();
	//glTranslatef(100,0,100);
	//draw_colony(100, _tex_colony);
	//glPopMatrix();
}

//void Drawing_engine::draw_test_ants(Ant_Sim *ant_sim_ptr,int hq_frame,int anim_frame)
//{
//	for (int cnt = 0; cnt < ant_sim_ptr->_ant_number; cnt++) 
//	{
//		glPushMatrix();
//			glTranslatef(ant_sim_ptr->_ant_posx[cnt],ant_sim_ptr->_ant_posy,ant_sim_ptr->_ant_posz[cnt]);
//			glRotatef(ant_sim_ptr->_ant_angley,0.0,1.0,0.0);
//			if (_high_quality_on) { _ant_hq_array[hq_frame]->draw_model(); }
//			else { draw_ant_anim(ant_sim_ptr->_ant_size, ant_color, anim_frame); }
//		glPopMatrix();
//	}
//}

void Drawing_engine::draw_ants(Ant_Sim *ant_sim_ptr, int round_cnt)
{
	//for low quality ants
	double ant_color[3] =  {0.2, 0.0, 0.0};
	int freq = 50;
	double anim_frame = std::abs((round_cnt%freq)/(0.25*freq)-2)-1;

	//for high quality ants
	int hq_frame = (round_cnt%16)/2;

	//draw all ants in the environment list
	std::list<std::shared_ptr<Ant>> ant_list = (*ant_sim_ptr)._table_items->_ant_list;
	for (std::list<std::shared_ptr<Ant>>::iterator ant_it = ant_list.begin(); ant_it != ant_list.end() ; ++ant_it)
	{ 
		Position ant_pos = (*ant_it)->_pos;
		glPushMatrix();
			glTranslatef(ant_pos._x,ant_pos._y,ant_pos._z);
			double ant_angle_rad = M_PI;
			if (ant_pos._direction[1] != -1)
				ant_angle_rad = 2*atan(ant_pos._direction[0]/(1+ant_pos._direction[1]));
			double ant_angle_deg = 180 + ant_angle_rad * 180 / M_PI;
			glRotated(ant_angle_deg, 0.0, 1.0, 0.0);
			if (_high_quality_on) { _ant_hq_array[hq_frame]->draw_model(); }
			else { draw_ant_anim((*ant_it)->get_size(), ant_color, anim_frame); }
		glPopMatrix();
	}

	//draw_test_ants(ant_sim_ptr,hq_frame,anim_frame);
}

void Drawing_engine::draw_location_selected_on_board(void)
{ // function to select position on board by mouse click
  // not yet ready (distortion in the corners)
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3))
	// right mouse click
	{
		std::vector<double> pos_on_board = _camera.calculate_click_point(BOARD_SIZE);
		// returns {-1, -1} if mouse does not point on board
		if (pos_on_board[0] != -1)
		{
			glPushMatrix();
				glTranslatef(pos_on_board[0],2,pos_on_board[1]);
				draw_pic(100, _tex_apple_top);
			glPopMatrix();
		}
	}
}

void Drawing_engine::draw_result(double result)
{
	// result must be given between 0 and 1
	double disp_result = result*60;
	glPushMatrix();
		glTranslatef(200,200,200);
		glRotatef(135.0,0.0,1.0,0.0);
		draw_pic(100,_tex_result);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(172,166+disp_result,215);
		glRotatef(135.0,0.0,1.0,0.0);
		draw_pic(30,_tex_result_pointer);
	glPopMatrix();
}

void Drawing_engine::clean_up(void)
{
	SDL_FreeSurface( _prescreen );
	SDL_FreeSurface( _screen );
	SDL_FreeSurface( _logo );
	kill_skybox();
	glDeleteTextures(1,&_tex_board);
	glDeleteTextures(1,&_tex_border);
	glDeleteTextures(1,&_tex_colony);
	glDeleteTextures(1,&_tex_box);
	glDeleteTextures(1,&_tex_apple_side);
	glDeleteTextures(1,&_tex_apple_top);
	glDeleteTextures(1,&_tex_logo);
	glDeleteTextures(1,&_tex_result);
	glDeleteTextures(1,&_tex_result_pointer);
	for (int i = 0; i <= 7; i++)
	{
		delete(_ant_hq_array[i]);
	}
	delete(_apple_hq);
}

void Drawing_engine::start_countdown(void)
{
	_countdown_on = true;

	// warp to start position to look at the result
	_camera._camX = 85;
	_camera._camY = 220;
	_camera._camZ = 105;
	_camera._camPitch = 0;
	_camera._camYaw = 225;
}

void Drawing_engine::print_cam_pos(void)
{
	_camera.print();
}

void Drawing_engine::switch_fog_no_fog(void)
{
	_switch_fog_on= !_switch_fog_on;
	if (_switch_fog_on) { glEnable(GL_FOG); }
	else {glDisable(GL_FOG); }
}

void Drawing_engine::switch_good_bad_graphics(void)
{
	_high_quality_on = !_high_quality_on;
}

void Drawing_engine::left_mouse_click(void)
{
	_mousein = true;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouse(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
}

void Drawing_engine::left_mouse_unclick(void)
{
	_mousein = false;
	SDL_ShowCursor(SDL_ENABLE);
}

void Drawing_engine::go_into_building_menu(void)
{
}

void Drawing_engine::draw_building_menu(void)
{

}

void Drawing_engine::display(Ant_Sim *ant_sim_ptr, Uint32 time_remaining, int round_cnt)
{
	// in color_buffer the color of every pixel is saved
	// in depth buffer the depth of every pixel is saved (which px is in front of which)
	// usually, it makes sense to clean the buffers after every frame
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	// switch back to normal cavalier projection with view of 45°
	switch_to_normal_perspective(45);

	// calculate camera moving speed (with accelaration)
	if (_keystates[SDLK_LSHIFT]) 
		{ _recent_cam_velocity = std::min<int>(_recent_cam_velocity+1,50); }
	else 
		{ _recent_cam_velocity = _cam_velocity; }
	_camera.control(_recent_cam_velocity,0.5,BOARD_SIZE,SCREEN_WIDTH,SCREEN_HEIGHT,_mousein);

	// draw skybox, don't make it bigger than the far-view-plane (see gluPerspective)
	draw_skybox(SKY_BOY_DISTANCE);

	_camera.update();
	draw_board(BOARD_SIZE, _tex_board);
	draw_border(BOARD_SIZE, _tex_border);
	draw_colonies(ant_sim_ptr);
	draw_obstacles(ant_sim_ptr);
	draw_foods(ant_sim_ptr);
	draw_ants(ant_sim_ptr, round_cnt);

	if (_building_menu_on)
		draw_building_menu();
	if (_countdown_on) 
	{ 
		double result = calc_result(ant_sim_ptr);
		draw_result(result); 
	}

	glPushMatrix();
		switch_to_ortho_perspective();
		draw_hud(time_remaining, ant_sim_ptr);
	glPopMatrix();
	glFlush();
}