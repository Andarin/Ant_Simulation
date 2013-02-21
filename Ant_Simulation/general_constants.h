#pragma once
#include <string>

#ifndef M_PI    //if the pi is not defined in the cmath header file
#define M_PI 3.1415926535       //define it
#endif

// give the window resolution
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
// give the size of the board in millimeters
const int BOARD_SIZE = 5000;
// write here the name of the file where the parameters are stored
const std::string FILE_NAME = "Ant_Sim_parameters.txt";
// the distance of the sky in millimeters
const double SKY_BOY_DISTANCE = 9000.0;

// every object has an ID to, in case, identify which object is currently handled
const int OBJECT_TYPE_NR_OF_COLONY = 0;
const int OBJECT_TYPE_NR_OF_ANT = 1;
const int OBJECT_TYPE_NR_OF_FOOD = 2;
const int OBJECT_TYPE_NR_OF_PHEROMONE = 3;
const int OBJECT_TYPE_NR_OF_OBSTACLE = 4;

// in an ant colony, there are different classes; these are there IDs
// to give them different tasks
// currently, there is only the worker class implemented
const int ANT_TYPE_NR_OF_WORKER = 0;
const int ANT_TYPE_NR_OF_SOLDIER = 1;

// ants can place different kinds of pheromones
// these are the IDs of the different kinds of pheromones
const int PHERO_TYPE_FOOD = 0;
const int PHERO_TYPE_ALERT = 1;

// the IDs of possible objectives of one ant
const int ANT_STATUS_SCOUT = 0;			//to find new foods
const int ANT_STATUS_BACK_TO_COLONY = 1;//to bring back food to colony or to go back to it to get energy...
const int ANT_STATUS_GET_FOOD = 2;		//to go and take food from an already discovered food

//Different type of pheromone for the simple AI:
const int SIMPLE_AI_PHERO_BACK = 0;//is used when the ant searchs for a way to go back to the colony
const int SIMPLE_AI_PHERO_FOOD = 1;//is used when the ant searchs for food


