#include "Timer.h"

Timer::Timer() : start_tick(0), paused_tick(0), is_paused(false), is_started(true) {}

void Timer::start() {
	is_started = true;
	is_paused = false;
	start_tick = SDL_GetTicks();
}

void Timer::stop() {
	is_paused = true;
	is_started = false;
}

void Timer::paused() {
    if (is_started && !is_paused) {
        is_paused = true;
        paused_tick = SDL_GetTicks() - start_tick;
    }
}

void Timer::unpaused() {
    if (is_paused) {
        is_paused = false;
        start_tick = SDL_GetTicks() - paused_tick;
        paused_tick = 0;
    }
}
int Timer::getTicks() {
  if (is_started && !is_paused) {
    return SDL_GetTicks() - start_tick;
  }
  return paused_tick;
}

bool Timer::isStarted()
{
	return is_started;
}

bool Timer::isPaused()
{
	return is_paused;
}
