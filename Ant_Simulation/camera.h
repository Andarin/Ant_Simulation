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
#include <vector>
#include "general_constants.h"
#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	Camera(void);
	~Camera(void);

	float _camX; 
	float _camY;
	float _camZ;       //current position of the camera
	float _camYaw;       //camera rotation in Y axis
	float _camPitch;     //camera rotation in X axis

	void lock(int);
	void move(float,float);
	void move_camera_up(float,float);
	void control(float,float,int,int,int,bool);
	void update(void);
	void print(void);
	std::vector<double> calculate_click_point(int);
};

#endif
