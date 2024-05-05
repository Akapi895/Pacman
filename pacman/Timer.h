#ifndef TIMER_H
#define TIMER_H
#include "CommonFunction.h"

class Timer
{
public:
	Timer();
	~Timer() { ; }

	void start();
	void stop();

	void paused();
	void unpaused();

	int getTicks();

	bool isStarted();
	bool isPaused();

private:
	int start_tick;
	int paused_tick;

    bool is_started;
	bool is_paused;
};


#endif
