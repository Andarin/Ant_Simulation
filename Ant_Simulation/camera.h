    //This example program is created by thecplusplusuy for demonstration purposes. It's a simple 3D FPS camera:
    //http://www.youtube.com/user/thecplusplusguy
    //Free source, modify if you want, LGPL licence (I guess), I would be happy, if you would not delete the link
    //so other people can see the tutorial
    //this file is functions.h, it's contain the function prototypes for the camera
#pragma once
#ifdef _WIN32
	#include "windows.h"
	#include <SDL.h>
#else
	#include <SDL/SDL.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
#ifndef CAMERA_H
#define CAMERA_H

void lock_camera(int);
void move_camera(float,float);
void move_camera_up(float,float);
void camera_control(float,float,int,int,int,bool);
void update_camera();
void print_camera_pos();
#endif
