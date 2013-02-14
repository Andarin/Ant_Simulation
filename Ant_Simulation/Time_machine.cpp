#include "Time_machine.h"

Time_machine::Time_machine(void)
{
	_current_time = SDL_GetTicks();
	_time_stopper = 0;
	_round_cnt_save = 0;
	_frame_cnt_save = 0;
	_frame_cnt = 0;
}

Time_machine::~Time_machine(void)
{
}


Uint32 Time_machine::return_frame_time(void)
{
	Uint32 new_time = SDL_GetTicks();
	Uint32 frame_time = new_time - _current_time;
	_current_time = new_time;
	_frame_cnt++; // keep on track how many frames were flipped
	return frame_time;
}

void Time_machine::print_time_status(int round_cnt, int sim_time_step)
{
	Uint32 new_time = SDL_GetTicks();
	// calculate and print frame rate
	if (new_time-_time_stopper  > 3000) {
		float rounds = (round_cnt-_round_cnt_save) / ( (new_time-_time_stopper) / 1000.f );
		std::cout << "Rounds per realtime sec: " << rounds
			    << " = " << sim_time_step * rounds / 1000
				<< " simulation sec by " 
				<< (_frame_cnt-_frame_cnt_save) / ( (new_time-_time_stopper) / 1000.f )
				<< " FPS."<< std::endl;
		_time_stopper = new_time;
		_round_cnt_save = round_cnt;
		_frame_cnt_save = _frame_cnt;
	}
}