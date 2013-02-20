#include "models.h"

void draw_board(int size, unsigned int tex_grass)
{
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


void draw_ant(int size, double color[])
{
 glBegin(GL_QUADS);
  // head
  glColor4f(color[0],color[1],color[2],1.0);
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

void draw_ant_anim(int size, double color[], double anim_step)
{
	double change_in_y = 0.3;
	glBegin(GL_QUADS);
	// head
	glColor4f(color[0],color[1],color[2],1.0);
	glVertex3f(0.0,change_in_y,0.0);
	glVertex3f(0.35*size,change_in_y,0.0);
	glVertex3f(0.35*size,change_in_y+0.35*size,0.0);
	glVertex3f(0.0,change_in_y+0.35*size,0.0);
	// antenna
	glVertex3f(0.35*size,change_in_y+0.35*size,0.0);
	glVertex3f(0.6*size,change_in_y+0.5*size,-0.1*size);
	glVertex3f(0.6*size,change_in_y+0.54*size,-0.1*size);
	glVertex3f(0.31*size,change_in_y+0.35*size,0.0);

	glVertex3f(0.0,change_in_y+0.35*size,0.0);
	glVertex3f(-0.15*size,change_in_y+0.5*size,-0.1*size);
	glVertex3f(-0.15*size,change_in_y+0.54*size,-0.1*size);
	glVertex3f(0.04*size,change_in_y+0.35*size,0.0);
	// body
	glVertex3f(0.0,change_in_y,0.0);
	glVertex3f(0.0,change_in_y,size);
	glVertex3f(0.35*size,change_in_y,size);
	glVertex3f(0.35*size,change_in_y,0.0);
	// left front leg
	glVertex3f(0.0,change_in_y,0.0);
	glVertex3f(0.0,change_in_y,0.1*size);
	glVertex3f(-0.5*size,change_in_y-0.4*size,0.6*anim_step*size-0.05*size);
	glVertex3f(-0.5*size,change_in_y-0.4*size,0.6*anim_step*size+0.1*size);
	// left middle leg
	glVertex3f(0.0,change_in_y,0.43*size);
	glVertex3f(0.0,change_in_y,0.57*size);
	glVertex3f(-0.5*size,change_in_y-0.4*size,-0.6*anim_step*size+0.53*size);
	glVertex3f(-0.5*size,change_in_y-0.4*size,-0.6*anim_step*size+0.43*size);
	// left back leg
	glVertex3f(0.0,change_in_y,0.9*size);
	glVertex3f(0.0,change_in_y,size);
	glVertex3f(-0.5*size,change_in_y-0.4*size,0.6*anim_step*size+0.95*size);
	glVertex3f(-0.5*size,change_in_y-0.4*size,0.6*anim_step*size+1.05*size);
	// right front leg
	glVertex3f(0.35*size,change_in_y,0.0);
	glVertex3f(0.35*size,change_in_y,0.14*size);
	glVertex3f(0.85*size,change_in_y-0.4*size,-0.6*anim_step*size-0.05*size);
	glVertex3f(0.85*size,change_in_y-0.4*size,-0.6*anim_step*size+0.1*size);
	// right middle leg
	glVertex3f(0.35*size,change_in_y,0.43*size);
	glVertex3f(0.35*size,change_in_y,0.57*size);
	glVertex3f(0.85*size,change_in_y-0.4*size,0.6*anim_step*size+0.53*size);
	glVertex3f(0.85*size,change_in_y-0.4*size,0.6*anim_step*size+0.43*size);
	// right back leg
	glVertex3f(0.35*size,change_in_y,0.83*size);
	glVertex3f(0.35*size,change_in_y,size);
	glVertex3f(0.85*size,change_in_y-0.4*size,-0.6*anim_step*size+0.95*size);
	glVertex3f(0.85*size,change_in_y-0.4*size,-0.6*anim_step*size+1.05*size);
	glEnd();
}

void draw_colony(int size, unsigned int tex_colony)
{
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D,tex_colony);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-size/2.0,0,-size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(-size/2.0,0,size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(0,size,size/2.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(0,size,-size/2.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_colony);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(size/2.0,0,-size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size/2.0,0,size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(0,size,size/2.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(0,size,-size/2.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_colony);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-size/2.0,0,size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size/2.0,0,size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(size/2.0,size,0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(-size/2.0,size,0);
  glEnd();

   glBindTexture(GL_TEXTURE_2D,tex_colony);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-size/2.0,0,-size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size/2.0,0,-size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(size/2.0,size,0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(-size/2.0,size,0);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void draw_box(int size, unsigned int tex_sides, unsigned int tex_top)
{
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D,tex_sides);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-size/2.0,0,-size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(-size/2.0,0,size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(-size/2.0,size,size/2.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(-size/2.0,size,-size/2.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_sides);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(size/2.0,0,-size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size/2.0,0,size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(size/2.0,size,size/2.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(size/2.0,size,-size/2.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_sides);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-size/2.0,0,size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size/2.0,0,size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(size/2.0,size,size/2.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(-size/2.0,size,size/2.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_sides);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-size/2.0,0,-size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size/2.0,0,-size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(size/2.0,size,-size/2.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(-size/2.0,size,-size/2.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,tex_top);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-size/2.0,size,-size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(size/2.0,size,-size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(size/2.0,size,size/2.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(-size/2.0,size,size/2.0);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void draw_pic(int size, unsigned int tex_pic)
{
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D,tex_pic);
  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,1.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(0,-size/2.0,-size/2.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(0,-size/2.0,size/2.0);
  glTexCoord2f(0.0,0.0);
  glVertex3f(0,size/2.0,size/2.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(0,size/2.0,-size/2.0);
  glEnd();
}