//This example program is created by thecplusplusuy for demonstration purposes. 
//It's a simple 3D FPS camera:
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, 
//if you would not delete the link
//so other people can see the tutorial
//this file is functions.h, it's contain the actual implementation of the 3D camera

//Edited by Lucas Tittmann, 02/13
//added some functionality and made the camera an object

#include "Camera.h"

Camera::Camera(void)
{
	_camX = 71; 
	_camY = 128;
	_camZ = 59;
	_camYaw	= 229;       //camera rotation in Y axis
	_camPitch = -15;     //camera rotation in X axis

	_camX_saved = 71; 
	_camY_saved = 128;
	_camZ_saved = 59;
	_camYaw_saved = 229;    //camera rotation in Y axis
	_camPitch_saved = -15;  //camera rotation in X axis
}

Camera::~Camera(void)
{
}

void Camera::lock(int board_size)
{
    //set campitch between -90 and 90 and set camyaw between 0 and 360 degrees
    if(_camPitch>90)
		_camPitch=90;
    if(_camPitch<-90)
        _camPitch=-90;
    if(_camYaw<0.0)
        _camYaw+=360.0;
    if(_camYaw>360.0)
        _camYaw-=360;
	_camX = std::max<double>(_camX,5);
	_camX = std::min<double>(_camX,board_size-5);
	_camZ = std::max<double>(_camZ,5);
	_camZ = std::min<double>(_camZ,board_size-5);
	_camY = std::max<double>(_camY,5);
	_camY = std::min<double>(_camY,300);
}
 
void Camera::move(float dist,float dir)
{
    float rad=(_camYaw+dir)*M_PI/180.0; //convert the degrees into radians
    _camX-=sin(rad)*dist;    //calculate the new coordinate
    _camZ-=cos(rad)*dist;
}
 
void Camera::move_camera_up(float dist,float dir)
{
    //the the same, only this time we calculate the y coorinate
    float rad=(_camPitch+dir)*M_PI/180.0;
    _camY+=sin(rad)*dist;   
}
 
void Camera::control(float movevel, float mousevel, int board_size, 
					int screen_w, int screen_h, bool mouse_in_window)
{
    if(mouse_in_window)  //if the mouse is in the screen
    {
        int MidX=screen_w/2;   //middle of the screen
        int MidY=screen_h/2;
        SDL_ShowCursor(SDL_DISABLE);    //we don't show the cursor
        int tmpx,tmpy;
        SDL_GetMouseState(&tmpx,&tmpy); //get the current position of the cursor
        _camYaw += mousevel*(MidX-tmpx);   //get the rotation
        _camPitch += mousevel*(MidY-tmpy); //this is for X
        lock(board_size);
        SDL_WarpMouse(MidX,MidY);       //move back the cursor to the center of the screen
        Uint8* state=SDL_GetKeyState(NULL);     //which key is pressed?
        if(state[SDLK_w])
        {
			 //if we are facing directly up or down, we don't go forward
            if(_camPitch!=90 && _camPitch!=-90)
                    move(movevel,0.0); //move forward
            move_camera_up(movevel,0.0);      //move up/down
        } else if(state[SDLK_s])
        {
            //same, just we use 180 degrees, so we move at the different direction (move back)
            if(_camPitch!=90 && _camPitch!=-90)
                move(movevel,180.0);
            move_camera_up(movevel,180.0);
        }              
        if(state[SDLK_a])       //move left
            move(movevel,90.0);
        else if(state[SDLK_d])  //move right
            move(movevel,270);       
    }
    glRotatef(-_camPitch,1.0,0.0,0.0); //rotate the camera
    glRotatef(-_camYaw,0.0,1.0,0.0);
}
 
void Camera::update(void)
{
    glTranslatef(-_camX,-_camY,-_camZ); //move the camera
}

void Camera::print(void)
{
	std::cout << "x: " << _camX <<" - y: " << _camY <<" - z: " << _camZ 
		<< " - camPitch: " << _camPitch << " - camYaw: " << _camYaw << std::endl;
}

std::vector<double> Camera::calculate_click_point(int map_size)
{
	// caculates where on the board was clicked on
	// returns -1, -1 of coords not on board
	double x_on_board;
	double z_on_board;
	std::vector<double> board_pos;
    int tmpx,tmpy;

	SDL_GetMouseState(&tmpx,&tmpy);
	// calculate pitch of mouse pointer in rad
	float click_pitch_deg = 45.0*(screen_height/2.0 - tmpy)/screen_height;
	float anti_angle_deg = 90 + _camPitch + click_pitch_deg;
	float anti_angle_pi = anti_angle_deg / 180 * M_PI;
	// now we can calculate the distance to the camera
	float distance = std::tan(anti_angle_pi)*_camY;

	// now calculate the position on the circle
	float click_yaw_deg =60.0*(screen_width/2.0 - tmpx)/screen_width;
	float angle_yaw_deg = 270 - _camYaw - click_yaw_deg;
	float angle_yaw_pi = angle_yaw_deg / 180 * M_PI;

	x_on_board = _camX + std::cos(angle_yaw_pi)*distance;
	z_on_board = _camY + std::sin(angle_yaw_pi)*distance;

	// sanitize user input
	if (anti_angle_deg >= 90
		|| x_on_board < map_size/50 || x_on_board > map_size*49/50
		|| z_on_board < map_size/50 || z_on_board > map_size*49/50) 
	{
		x_on_board = -1;
		z_on_board = -1;
	}

	//std::cout << tmpx << " " << angle_yaw_deg <<" "<<x_on_board<<" "<<z_on_board<< std::endl;
	//std::cout << _camX << " " << _camY << " " << _camZ << std::endl;
	board_pos.push_back(x_on_board);
	board_pos.push_back(z_on_board);
	return board_pos;
}

void Camera::save_current_pos(void)
{
	_camX_saved = _camX;
	_camY_saved = _camY;
	_camZ_saved = _camZ;
	_camPitch_saved = _camPitch;
	_camYaw_saved = _camYaw;
}

void Camera::load_last_pos(void)
{
	_camX = _camX_saved;
	_camY = _camY_saved;
	_camZ = _camZ_saved;
	_camPitch = _camPitch_saved;
	_camYaw = _camYaw_saved;
}