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
#include <windows.h>
#include <SDL.h>
//#include <SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>
#include <time.h>
#include "glext.h"

// self-created external depencies
#include "camera.h"
#include "skybox.h"
#include "models.h"
#include "general_constants.h"

using namespace std;

// user changeable parameters
int FPS = 40;
const int screen_width = 960;
const int screen_height = 640;
const int ant_number = 5000;
const int board_size = 5000;
const bool SWITCH_FOG_ON = true;
const double SKY_BOY_DISTANCE = 5000.0;
int cam_velocity = 1;

// system variables
int round_cnt = 0;
bool mousein = false;
unsigned int tex_board;
unsigned int tex_border;
Uint8 *keystates = SDL_GetKeyState( NULL );
int ant_model;

// just for testing / not important
float ant_posx[ant_number];
float ant_posz[ant_number];
float ant_posy = 2;
float ant_size = 4;
float ant_angley = 180;

void move_ants()
{
	int velocity = (round_cnt%450)/45;	 
	switch(velocity) {
	case 0:
		ant_size += 0.2;
		ant_posy += 0.1; break;
	case 1:
		for (int cnt = 0; cnt < ant_number; cnt++) {ant_posz[cnt] += 1;}
		break;
	case 3:
		for (int cnt = 0; cnt < ant_number; cnt++) {ant_posx[cnt] += 1;}
		break;
	case 5:
		ant_size -= 0.2;
		ant_posy -= 0.1; break;
	case 6:
		for (int cnt = 0; cnt < ant_number; cnt++) {ant_posz[cnt] -= 1;}
		break;
	case 8:
		for (int cnt = 0; cnt < ant_number; cnt++) {ant_posx[cnt] -= 1;}
		break;
	default:
		ant_angley += 90/45; break;
	}
}

void init()
{
	SDL_WM_SetCaption( "Ant Simulation", NULL );
	glClearColor(0.2,0.2,0.8,1.0); //background color and alpha
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(1.0*screen_width)/screen_height,1.0,5000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	if (SWITCH_FOG_ON)
	{ 
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE,GL_LINEAR);
		glFogf(GL_FOG_START,800.0);
		glFogf(GL_FOG_END,3000.0);
		float fog_color[] = {0.33,0.5,.80,0.7};
		glFogfv(GL_FOG_COLOR,fog_color);
	}
	init_skybox();
	tex_board=load_texture_png("src/grass.png", 512, 512, false, true);
	tex_border=load_texture_png("src/border.png", 1024, 1024);
	for (int cnt = 0; cnt < ant_number; cnt++)
	{
		ant_posx[cnt] = rand() % (board_size-40) + 20;
		ant_posz[cnt] = rand() % (board_size-40) + 20;
	}
}

void display()
{
	// in color_buffer the color of every pixel is saved
	// in depth buffer the depth of every pixel is saved (which px is in front of which)
	// usually, it makes sense to clean the buffers after every frame
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	int recent_cam_velocity = 1;
	if(keystates[SDLK_LSHIFT])
		recent_cam_velocity *= 4;
	camera_control(recent_cam_velocity,0.5,board_size,screen_width,screen_height,mousein);
	draw_skybox(SKY_BOY_DISTANCE); // don't make it bigger than the far-view-plane (see gluPerspective)
	update_camera();
	draw_board(board_size, tex_board);
	draw_border(board_size, tex_border);

	glCallList(ant_model);
	for (int cnt = 0; cnt < ant_number; cnt++) 
	{
		glPushMatrix();
			glTranslatef(ant_posx[cnt],ant_posy,ant_posz[cnt]);
			glRotatef(ant_angley,0.0,1.0,0.0);
			draw_ant(ant_size);
		glPopMatrix();
	}
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen;
	// SDL_SWSURFACE|SDL_OPENGL means: do both options
	screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE|SDL_OPENGL);
	//screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE|SDL_FULLSCREEN);
	
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

	while(running) {
		////////////////////////////////////////////////////////
		/////////////         EVENT HANDLING      //////////////
		////////////////////////////////////////////////////////
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running = false; break;
				case SDL_MOUSEBUTTONDOWN:
					mousein = true;
					SDL_ShowCursor(SDL_DISABLE);
					SDL_WarpMouse(screen_width/2,screen_height/2);
					break;
				case SDL_MOUSEBUTTONUP:
					mousein = false;
					SDL_ShowCursor(SDL_ENABLE);
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym) {
						case SDLK_p:
							print_camera_pos(); break;	
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
			float rounds = (round_cnt-round_cnt_save) / ( (new_time-time_stopper) / 1000.f );
			cout << "Rounds per realtime sec: " << rounds
			     << " = " << time_step * rounds / 1000
				 << " simulation sec by " << (frame_cnt-frame_cnt_save) / ( (new_time-time_stopper) / 1000.f ) << " FPS."<< endl;
			time_stopper = new_time;
			round_cnt_save = round_cnt;
			frame_cnt_save = frame_cnt;
		}

		////////////////////////////////////////////////////////
		/////////////            GAME LOGIC       //////////////
		////////////////////////////////////////////////////////
		while ( accumulator >= time_step )
		{
			round_cnt++;
			move_ants();

			// operations to hold constant time flux
			accumulator -= time_step;
			time += time_step;
		}
		frame_cnt++;
		////////////////////////////////////////////////////////
		/////////////        GRAPHIC RENDERING    //////////////
		////////////////////////////////////////////////////////
		display();
		SDL_GL_SwapBuffers(); // blits the buffer to the screen
		
	}
	SDL_Quit();
	kill_skybox();
	glDeleteTextures(1,&tex_board);
	glDeleteTextures(1,&tex_border);
	return 0;
}