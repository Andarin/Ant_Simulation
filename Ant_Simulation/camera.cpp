//This example program is created by thecplusplusuy for demonstration purposes. 
//It's a simple 3D FPS camera:
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, 
//if you would not delete the link
//so other people can see the tutorial
//this file is functions.h, it's contain the actual implementation of the 3D camera
#include "camera.h"

float camX		=71; 
float camY		=128;
float camZ		=59;       //current position of the camera
float camYaw	=229;       //camera rotation in Y axis
float camPitch	=-15;     //camera rotation in X axis
#ifndef M_PI    //if the pi is not defined in the cmath header file
#define M_PI 3.1415926535       //define it
#endif

void lock_camera(int board_size)
{
    //set campitch between -90 and 90 and set camyaw between 0 and 360 degrees
    if(camPitch>90)
		camPitch=90;
    if(camPitch<-90)
        camPitch=-90;
    if(camYaw<0.0)
        camYaw+=360.0;
    if(camYaw>360.0)
        camYaw-=360;
	camX = std::max<double>(camX,5);
	camX = std::min<double>(camX,board_size-5);
	camZ = std::max<double>(camZ,5);
	camZ = std::min<double>(camZ,board_size-5);
	camY = std::max<double>(camY,5);
	camY = std::min<double>(camY,300);
}
 
void move_camera(float dist,float dir)
{
    float rad=(camYaw+dir)*M_PI/180.0; //convert the degrees into radians
    camX-=sin(rad)*dist;    //calculate the new coordinate
    camZ-=cos(rad)*dist;
}
 
void move_camera_up(float dist,float dir)
{
    //the the same, only this time we calculate the y coorinate
    float rad=(camPitch+dir)*M_PI/180.0;
    camY+=sin(rad)*dist;   
}
 
void camera_control(float movevel, float mousevel, int board_size, 
					int screen_w, int screen_h, bool mouse_in_window)
{
    if(mouse_in_window)  //if the mouse is in the screen
    {
        int MidX=screen_w/2;   //middle of the screen
        int MidY=screen_h/2;
        SDL_ShowCursor(SDL_DISABLE);    //we don't show the cursor
        int tmpx,tmpy;
        SDL_GetMouseState(&tmpx,&tmpy); //get the current position of the cursor
        camYaw+=mousevel*(MidX-tmpx);   //get the rotation
        camPitch+=mousevel*(MidY-tmpy); //this is for X
        lock_camera(board_size);
        SDL_WarpMouse(MidX,MidY);       //move back the cursor to the center of the screen
        Uint8* state=SDL_GetKeyState(NULL);     //which key is pressed?
        if(state[SDLK_w])
        {
			 //if we are facing directly up or down, we don't go forward
            if(camPitch!=90 && camPitch!=-90)
                    move_camera(movevel,0.0); //move forward
            move_camera_up(movevel,0.0);      //move up/down
        }else if(state[SDLK_s])
        {
            //same, just we use 180 degrees, so we move at the different direction (move back)
            if(camPitch!=90 && camPitch!=-90)
                move_camera(movevel,180.0);
            move_camera_up(movevel,180.0);
        }              
        if(state[SDLK_a])       //move left
            move_camera(movevel,90.0);
        else if(state[SDLK_d])  //move right
            move_camera(movevel,270);       
    }
    glRotatef(-camPitch,1.0,0.0,0.0); //rotate the camera
    glRotatef(-camYaw,0.0,1.0,0.0);
}
 
void update_camera()
{
    glTranslatef(-camX,-camY,-camZ); //move the camera
}

void print_camera_pos()
{
	cout << "x: " << camX <<" - y: " << camY <<" - z: " << camZ 
		<< " - camPitch: " << camPitch << " - camYaw: " << camYaw << endl;
}
