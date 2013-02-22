//Ant Simulation is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Authors: Guillaume Martinet, Lucas Tittmann
// Date: 02/2013
//
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
//
// Some code is based on the tutorials from:
// http://www.youtube.com/user/thecplusplusguy
// If so it is stated in the header. The original files are distributed under LPGL.
//
// Furthermore, to display text, we use glfont2 by Brad Fisher:
// https://students.cs.byu.edu/~bfish/glfont2.php
//
// As font we used Didact Gothic by Daniel Johnson
// http://openfontlibrary.org/en/font/didact-gothic#Didact%20Gothic-Medium
//
// For displaying PNG-images, we use loadpng by Lode Vandevenne
// http://lodev.org/lodepng/
//
// To display the Blender models (*.obj) in our simulation, we used code from
// the site du zero:
// http://www.siteduzero.com/informatique/tutoriels/charger-des-fichiers-obj/parser-les-formats-obj-et-mtl
// http://www.siteduzero.com/informatique/tutoriels/creez-des-programmes-en-3d-avec-opengl/plaquage-de-texture
//
// The source files are also GPL v3.0 with 1 exception:
// grass.png by Titus Tscharntke is taken from
// http://www.public-domain-image.com/full-image/textures-and-patterns-public-domain-images-pictures/grass-texture-public-domain-images-pictures/buffalo-grass-texture.jpg-copyright-friendly-photo.html

#pragma once

// libraries - extern
#ifdef _WIN32
	#include "windows.h"
	#include <SDL.h>
	#include <SDL_image.h>
#else
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
#endif
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glfont2.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <time.h>
#include "glext.h"
#include "OBJlib.h"

// self-created source files
#include "Camera.h"
#include "Collision_detector.h"
#include "Colony.h"
#include "Colony_birth_info.h"
#include "Drawing_engine.h"
#include "Food.h"
#include "Game_item.h"
#include "Game_item_birth_info.h"
#include "Obstacle.h"
#include "Position.h"
#include "Table_of_items.h"
#include "Time_machine.h"
#include "general_constants.h"
#include "loadpng_functions.h"
#include "models.h"
#include "skybox.h"

class Ant_Sim
{
public:
	Ant_Sim(void);
	~Ant_Sim(void);
	void start(void);

	std::shared_ptr<Table_of_items> _table_items;
	std::shared_ptr<Collision_detector> _coll_dect;

	// just for testing / not important
	//float *_ant_posx;
	//float *_ant_posz;
	//float _ant_posy;
	//float _ant_size;
	//float _ant_angley;
	//int _ant_number;

private:
	// simulation related variables
	int _round_cnt;
	Uint32 _time_remaining;
	Uint32 _sim_time_step;
	double _max_size_of_pheromone;
	double _max_size_of_vision;
	double _max_size_of_corps;

	// boolean checks
	bool _running;
	bool _countdown_on;

	// graphic related variables
	Drawing_engine _drawing_engine;
	Uint8 *_keystates;

	// methods
	void move_test_ants(void);
	void init(void);
	int read_play_time_from_file(std::string); 
	void add_colony(void);
	void add_food(double,int,int,int);
	void add_start_food(int);
	void add_obstacle(double,int,int,int);
	void handle_user_input(SDL_Event &event);
	void start_countdown(void);
	void game_logic(Uint32);
	void clean_up(void);
};
