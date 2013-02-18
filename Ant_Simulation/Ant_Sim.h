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

// Authors: Guillaume Martinet, Lucas Tittmann
// Date: 01/2013

// Some code is based on the tutorials from:
//http://www.youtube.com/user/thecplusplusguy
// If so it is stated in the header. The original files are distributed under LPGL.
//
//The source files are also GPL v3.0 with 1 exception:
//grass.bmp is taken from
//http://www.public-domain-image.com/full-image/textures-and-patterns-public-domain-images-pictures/grass-texture-public-domain-images-pictures/buffalo-grass-texture.jpg-copyright-friendly-photo.html
//by Titus Tscharntke

#pragma once

// libraries
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

// self-created external depencies
#include "Drawing_engine.h"
#include "Camera.h"
#include "loadpng_functions.h"
#include "skybox.h"
#include "models.h"
#include "general_constants.h"
#include "Time_machine.h"
#include "Table_of_objects.h"
#include "Collision_detector.h"

class Ant_Sim
{
public:
	Ant_Sim(int, int);
	~Ant_Sim(void);
	void start(void);

	// just for testing / not important
	float *_ant_posx;
	float *_ant_posz;
	float _ant_posy;
	float _ant_size;
	float _ant_angley;
	int _ant_number;

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
	bool _mousein;
	bool _countdown_on;
	bool _high_quality_on;
	bool _switch_fog_on;

	// graphic related variables
	Drawing_engine _drawing_engine;
	//Camera _camera;
	Uint8 *_keystates;

	// methods
	void move_ants(void);
	void init(void);

	void handle_user_input(SDL_Event &event);
	void clean_up(void);
	void start_countdown(void);
};
