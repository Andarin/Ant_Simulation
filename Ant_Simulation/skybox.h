//This example program is created by thecplusplusuy for demonstration purposes. It's a simple skybox:
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, if you would not delete the link
//so other people can see the tutorial
//this file is functions.h, it's contain the function prototypes
#pragma once
#include "lodepng.h"
#include "windows.h"
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "glext.h"

#ifndef SKYBOX_H
#define SKYBOX_H
     
void draw_skybox(float size);    //draw the skybox
void init_skybox();      //load the textures
void kill_skybox();      //delete the textures
unsigned int load_texture(const char*, bool);
unsigned int load_texture_png(const char*, unsigned, unsigned, bool);
#endif
