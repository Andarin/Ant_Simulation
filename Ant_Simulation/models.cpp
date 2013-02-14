#include "models.h"

void draw_board(int size, unsigned int tex_grass)
{
 glBegin(GL_QUADS);
  // front face
  glColor3f(0.4,0.4,0.0);
  glVertex3f(0,0,0);
  glVertex3f(0,-10,0);
  glVertex3f(size,-10,0);
  glVertex3f(size,0,0);
  // left face
  glColor3f(0.4,0.4,0.0);
  glVertex3f(0,0,0);
  glVertex3f(0,-10,0);
  glVertex3f(0,-10,size);
  glVertex3f(0,0,size);
  // back face
  glColor3f(0.4,0.4,0.0);
  glVertex3f(0,0,size);
  glVertex3f(0,-10,size);
  glVertex3f(size,-10,size);
  glVertex3f(size,0,size);
  // right face
  glColor3f(0.4,0.4,0.0);
  glVertex3f(size,0,0);
  glVertex3f(size,-10,0);
  glVertex3f(size,-10,size);
  glVertex3f(size,0,size);

  // bottom face
  glColor3f(0.4,0.4,0.0);
  glVertex3f(0,-10,0);
  glVertex3f(0,-10,size);
  glVertex3f(size,-10,size);
  glVertex3f(size,-10,0);
  glEnd();

  	int tex_repeat_rate = size/500;
  // top face
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,tex_grass);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(0,0,0);
  glTexCoord2f(0.0,tex_repeat_rate);
  glVertex3f(0,0,size);
  glTexCoord2f(tex_repeat_rate,tex_repeat_rate);
  glVertex3f(size,0,size);
  glTexCoord2f(tex_repeat_rate,0.0);
  glVertex3f(size,0,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void draw_border(int size, unsigned int tex_border)
{
	int tex_repeat_rate = size/250;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,tex_border);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(0,0,0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(0,300,0);
  glTexCoord2f(tex_repeat_rate,0.0);
  glVertex3f(size,300,0);
  glTexCoord2f(tex_repeat_rate,1.0);
  glVertex3f(size,0,0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_border);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size,0,0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(size,300,0);
  glTexCoord2f(tex_repeat_rate,0.0);
  glVertex3f(size,300,size);
  glTexCoord2f(tex_repeat_rate,1.0);
  glVertex3f(size,0,size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_border);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size,0,size);
  glTexCoord2f(0.0,0.0);
  glVertex3f(size,300,size);
  glTexCoord2f(tex_repeat_rate,0.0);
  glVertex3f(0,300,size);
  glTexCoord2f(tex_repeat_rate,1.0);
  glVertex3f(0,0,size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_border);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(0,0,size);
  glTexCoord2f(0.0,0.0);
  glVertex3f(0,300,size);
  glTexCoord2f(tex_repeat_rate,0.0);
  glVertex3f(0,300,0);
  glTexCoord2f(tex_repeat_rate,1.0);
  glVertex3f(0,0,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void draw_ant(int size)
{
 glBegin(GL_QUADS);
  // head
  glColor4f(0.0,0.0,0.0,1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.35*size,0.0,0.0);
  glVertex3f(0.35*size,0.35*size,0.0);
  glVertex3f(0.0,0.35*size,0.0);
  // antenna
  glVertex3f(0.35*size,0.35*size,0.0);
  glVertex3f(0.6*size,0.5*size,-0.1*size);
  glVertex3f(0.6*size,0.54*size,-0.1*size);
  glVertex3f(0.31*size,0.35*size,0.0);

  glVertex3f(0.0,0.35*size,0.0);
  glVertex3f(-0.15*size,0.5*size,-0.1*size);
  glVertex3f(-0.15*size,0.54*size,-0.1*size);
  glVertex3f(0.04*size,0.35*size,0.0);
  // body
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,size);
  glVertex3f(0.35*size,0.0,size);
  glVertex3f(0.35*size,0.0,0.0);
  // left front leg
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.14*size);
  glVertex3f(-0.5*size,-0.4*size,0.14*size);
  glVertex3f(-0.5*size,-0.4*size,0.0);
  // left middle leg
  glVertex3f(0.0,0.0,0.43*size);
  glVertex3f(0.0,0.0,0.57*size);
  glVertex3f(-0.5*size,-0.4*size,0.57*size);
  glVertex3f(-0.5*size,-0.4*size,0.43*size);
  // left back leg
  glVertex3f(0.0,0.0,0.83*size);
  glVertex3f(0.0,0.0,size);
  glVertex3f(-0.5*size,-0.4*size,size);
  glVertex3f(-0.5*size,-0.4*size,0.83*size);
  // right front leg
  glVertex3f(0.35*size,0.0,0.0);
  glVertex3f(0.35*size,0.0,0.14*size);
  glVertex3f(0.85*size,-0.4*size,0.14*size);
  glVertex3f(0.85*size,-0.4*size,0.0);
  // right middle leg
  glVertex3f(0.35*size,0.0,0.43*size);
  glVertex3f(0.35*size,0.0,0.57*size);
  glVertex3f(0.85*size,-0.4*size,0.57*size);
  glVertex3f(0.85*size,-0.4*size,0.43*size);
  // right back leg
  glVertex3f(0.35*size,0.0,0.83*size);
  glVertex3f(0.35*size,0.0,size);
  glVertex3f(0.85*size,-0.4*size,size);
  glVertex3f(0.85*size,-0.4*size,0.83*size);
 glEnd();
}