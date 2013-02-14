#pragma once
#include "lodepng.h"
#include "windows.h"
#include <SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "glext.h"

unsigned int load_texture(const char*, bool);
unsigned int load_texture_png(const char*, unsigned, unsigned, bool duplicate_pixel = false, bool mipmapping = false);
void apply_surface(int, int, SDL_Surface*, SDL_Surface*);
SDL_Surface *load_image(std::string);