#pragma once
#include <SDL.h>
#include <iostream>

class Time_machine
{
public:
	Time_machine(void);
	~Time_machine(void);	
	Uint32 return_frame_time(void);
	void print_time_status(int, int);

private:
	Uint32 _current_time;
	Uint32 _time_stopper;
	int _round_cnt_save;
	int _frame_cnt_save;
	int _frame_cnt;
};
