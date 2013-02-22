// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "loadpng_functions.h"

unsigned int load_texture(const char* filename, bool duplicate_pixels)
//load the filename named texture
{ 
    unsigned int num;       //the id for the texture
    glGenTextures(1,&num);  //we generate a unique one
    SDL_Surface* img=SDL_LoadBMP(filename); //load the bmp image
	//and use the texture, we have just generated
    glBindTexture(GL_TEXTURE_2D,num);       
	//if the texture is smaller, than the image, we get the avarege of the pixels next to it
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//same if the image bigger
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
	if (duplicate_pixels) 
	{
		//we repeat the pixels in the edge of the texture, 
		//it will hide that 1px wide line at the edge of the cube, 
		//which you have seen in the video
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		//we do it for vertically and horizontally (previous line)
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	}
	//we make the actual texture
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);
    SDL_FreeSurface(img);   //we delete the image, we don't need it anymore
    return num;     //and we return the id
}

unsigned int load_texture_png(const char* filename, unsigned width, unsigned height, bool duplicate_pixels, bool mipmapping)
//load the filename named texture
{
	// Load file and decode image.
	std::vector<unsigned char> image;
	unsigned error = lodepng::decode(image, width, height, filename);

	// If there's an error, display it.
	if(error != 0)
	{
		std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
		return 1;
	}
  
    unsigned int num;       //the id for the texture
    glGenTextures(1,&num);  //we generate a unique one
	//and use the texture, we have just generated
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5);
    glBindTexture(GL_TEXTURE_2D,num);       
	
	// 1) check of mipmapping (= texture antialising)
	if (mipmapping)
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );
	} else
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	}

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	if (duplicate_pixels) 
	{
		//we repeat the pixels in the edge of the texture, 
		//it will hide that 1px wide line at the edge of the cube, 
		//which you have seen in the video
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		//we do it for vertically and horizontally (previous line)
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	}

	if (mipmapping)	
	{
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &image[0] );
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]); 
	}

    return num;     //and we return the id
}

// from Lazy Foo's tutorial 3
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Rectangle to hold the offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

// from Lazy Foo's tutorial 3
SDL_Surface *load_image( std::string filename ) 
{ //The image that's loaded 
	SDL_Surface* loadedImage = NULL; 
	//The optimized image that will be used 
	SDL_Surface* optimizedImage = NULL; 
	//Load the image using SDL_image 
	loadedImage = IMG_Load( filename.c_str() ); 
	//If the image loaded 
	if( loadedImage != NULL ) 
	{ //Create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedImage ); 
		//Free the old image 
		SDL_FreeSurface( loadedImage ); 
	} 
	//Return the optimized image 
	return optimizedImage; 
}