#pragma once

#ifndef M_PI    //if the pi is not defined in the cmath header file
#define M_PI 3.1415926535       //define it
#endif

const int screen_width = 960;
const int screen_height = 640;
const int board_size = 5000;
const double SKY_BOY_DISTANCE = 9000.0;

const int OBJECT_TYPE_NR_OF_COLONY = 0;
const int OBJECT_TYPE_NR_OF_ANT = 1;
const int OBJECT_TYPE_NR_OF_FOOD = 2;
const int OBJECT_TYPE_NR_OF_PHEROMONE = 3;

const int ANT_TYPE_NR_OF_WORKER = 0;
const int ANT_TYPE_NR_OF_SOLDIER = 1;

const int PHERO_TYPE_FOOD = 0;
const int PHERO_TYPE_ALERT = 1;

//Possible objectives of one ant :
const int SCOUT = 0;//to find new foods
const int GO_BACK_TO_COLONY = 1;//to bring back food to colony or to go back to it to get energy...
const int GET_FOOD = 2;//to go and take food from an already discovered food