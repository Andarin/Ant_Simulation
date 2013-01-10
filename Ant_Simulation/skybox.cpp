//This example program is created by thecplusplusuy for demonstration purposes. It's a simple skybox:
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, if you would not delete the link
//so other people can see the tutorial
//this file is functions.cpp, it's contain the actual implementation of the skybox
#include "skybox.h"

//constants for the skybox faces, so we don't have to remember so much number
enum {SKY_LEFT=0,SKY_BACK,SKY_RIGHT,SKY_FRONT,SKY_TOP,SKY_BOTTOM};
unsigned int skybox[6]; //the ids for the textures
     
//load all of the textures, to the skybox array
void init_skybox()
{
    skybox[SKY_LEFT]=load_texture_png("src/left.png", 512,256,true);
    skybox[SKY_BACK]=load_texture_png("src/back.png", 512,256,true);
    skybox[SKY_RIGHT]=load_texture_png("src/right.png", 512,256,true);
    skybox[SKY_FRONT]=load_texture_png("src/front.png", 512,256,true);
    skybox[SKY_TOP]=load_texture_png("src/top.png", 512,512,true);
    skybox[SKY_BOTTOM]=load_texture("src/grass.bmp", true);
}

//delete all of the textures from the skybox array (to avoid memory leaks)
void kill_skybox()
{
     glDeleteTextures(6,&skybox[0]);
}
     
void draw_skybox(float size)
{
    bool b1=glIsEnabled(GL_TEXTURE_2D);     //new, we left the textures turned on, if it was turned on
    glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
    glDisable(GL_DEPTH_TEST);       //turn off depth texting
    glEnable(GL_TEXTURE_2D);        //and turn on texturing
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);  //use the texture we want
    glBegin(GL_QUADS);      //and draw a face
	glColor3f(1.0,1.0,1.0);
        //back face
        glTexCoord2f(0,0);      //use the correct texture coordinate
        glVertex3f(size/2,size/2,size/2);       //and a vertex
        glTexCoord2f(1,0);      //and repeat it...
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(1,1);
        glVertex3f(-size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(size/2,-size/2,size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
    glBegin(GL_QUADS);     
        //left face
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(1,0);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
    glBegin(GL_QUADS);     
        //front face
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,-size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
    glBegin(GL_QUADS);     
        //right face
        glTexCoord2f(0,0);
        glVertex3f(size/2,size/2,-size/2);
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_TOP]);          
    glBegin(GL_QUADS);                     
	//top face
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,size/2,-size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_BOTTOM]);               
    glBegin(GL_QUADS);     
        //bottom face
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(1,0);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();
//        glEnable(GL_LIGHTING); 
    glEnable(GL_DEPTH_TEST);
    if(!b1)
            glDisable(GL_TEXTURE_2D);
}
 
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

unsigned int load_texture_png(const char* filename, unsigned width, unsigned height, bool duplicate_pixels)
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
	//// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
	//size_t u2 = 1; while(u2 < width) u2 *= 2;
	//size_t v2 = 1; while(v2 < height) v2 *= 2;
	//// Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
	//double u3 = (double)width / u2;
	//double v3 = (double)height / v2;

	//// Make power of two version of the image.
	//std::vector<unsigned char> image2(u2 * v2 * 4);
	//for(size_t y = 0; y < height; y++)
	//for(size_t x = 0; x < width; x++)
	//for(size_t c = 0; c < 4; c++)
	//{
	//image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
	//}
	////we make the actual texture
	//glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    return num;     //and we return the id
}

