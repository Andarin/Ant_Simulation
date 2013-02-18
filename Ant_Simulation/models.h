#pragma once
#ifdef _WIN32
	#include "windows.h"
	#include <SDL.h>
#else
	#include <SDL/SDL.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#ifndef MODELS_H
#define MODELS_H

void draw_board(int,unsigned int);
void draw_border(int,unsigned int);
void draw_ant(int, double[]);
void draw_ant_anim(int, double[], double);
void draw_colony(int, unsigned int);
void draw_box(int, unsigned int, unsigned int);
void draw_pic(int, unsigned int);
#endif
