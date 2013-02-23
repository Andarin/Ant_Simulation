// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation

// This file creates an API to use loadpng.h and SDL_image and is based on
// a tutorial by Lazy Foo, the cplusplusguy (youtube) and examples of loadpng.h
#pragma once
#include "lodepng.h"
#ifdef _WIN32
	#include "windows.h"
	#include <SDL.h>
	#include <SDL_image.h>
#else
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "glext.h"

// load a texture from a BMP file
// parameters are the file name and if we want to duplicate one row of pixels
// to delete e.g. the black line at the skybox
unsigned int load_texture(const char*, bool);

// load a texture from a PNG file
// parameters are the file name, the width and height of the image, if we want
// to duplicate one row of pixels to delete e.g. the black line at the skybox
// and a booling to enable mipmapping (mipmapping stores a bunch of smaller 
// image versions in the RAM so that often repeated textures don't give
// artefacts and are faster displayed)
unsigned int load_texture_png(const char*, unsigned, unsigned, bool duplicate_pixel = false, bool mipmapping = false);

void apply_surface(int, int, SDL_Surface*, SDL_Surface*);
// another load image function which returns a surface
SDL_Surface *load_image(std::string);
