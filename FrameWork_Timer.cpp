#include "FrameWork.h"

using FrameWork::Timer;

Timer* Timer::singleton = NULL;

unsigned int Timer::fwt_getTime()
{
	return SDL_GetTicks();
}

void Timer::fwt_destroy()
{
	delete singleton;
}