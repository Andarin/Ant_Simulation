// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#pragma once
#ifdef _WIN32
	#include "windows.h"
	#include <SDL.h>
#else
	#include <SDL/SDL.h>
#endif
#include <iostream>

// class which keeps track on everything concerning time management in the
// simulation; it tries to keep the time passed in the simulation synchron
// with the real time passed to calculate it
class Time_machine
{
public:
	Time_machine(void);
	~Time_machine(void);	
	// return the time needed to render the 3D scene
	Uint32 return_frame_time(void);
	// give console output of frame rate and time passed in the simulation
	void print_time_status(int, int);

private:
	Uint32 _current_time;
	Uint32 _time_stopper;
	int _round_cnt_save;
	int _frame_cnt_save;
	int _frame_cnt;
};
