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
    skybox[SKY_LEFT]=load_texture_png("src/left.png", 512,256, true);
    skybox[SKY_BACK]=load_texture_png("src/back.png", 512,256,true);
    skybox[SKY_RIGHT]=load_texture_png("src/right.png", 512,256,true);
    skybox[SKY_FRONT]=load_texture_png("src/front.png", 512,256,true);
    skybox[SKY_TOP]=load_texture_png("src/top.png", 512,512,true);
    skybox[SKY_BOTTOM]=load_texture_png("src/grass.png", 512, 512,true);
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