#include "Timer.h"

// set the previous and current ticks to 0 to make sure it doesn't have junk data.
Timer::Timer() : prevTicks(0), currentTicks(0) {}

Timer::~Timer() {}

void Timer::Start()
{
	/*
	SDL_GetTicks() does two things:

	1) It gets things in milliseconds, hence the milli_to_sec variable is created.

	2) When this timer is started, they dont start at 0 as the timer will be started
	a bit after SDL was initialized.
	*/
	prevTicks = currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks()
{
	/*
	Updates the previous and current ticks. 
	Must set the [previous] equal to the [current] FIRST, doing [current]
	first then [previous] will set the [currrent] to 0.
	*/ 
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const
{
	/*
	Gets previous time from previous frame to current frame, in seconds.
	
	Quick Note:
	This happens as a float division, since we defined milli_to_sec varable 
	as a float. (We need that decimal)

	If we divide to ~1000 it would be an integer division, which can be dangerous, any
	sort of decimal will be cut off.
	*/
	return (currentTicks - prevTicks) / MILLI_TO_SEC;
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	/*
	 Will cap our engine to 60fps. 
	 
	 Not having a sleep time can potentially allow the engine to run faster than 60 fps. 
	 
	 It's a MUST that an engine is consistent, it's important for physics and or networking.
	 
	 It stops the GPU from "burning out", which can be a problem with improper cooling.
	*/
	unsigned int milliSecsPerFrame = MILLI_TO_SEC / fps_;
	if (milliSecsPerFrame == 0)
	{
		return 0;
	}

	/*
	Calculates how much sleep time the engine needs to see.

	This makes sure that the engine sleeps for the least amount of time needed.
	*/ 
	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currentTicks);
	if (sleepTime > milliSecsPerFrame)
	{
		return milliSecsPerFrame;
	}


	return sleepTime;
}

float Timer::GetCurrentTickMilli() const
{
	/*
	Gets total millisecond time, cast current ticks to a float.

	Casting removes warnings that will occur, although it doesn't 
	really do anything.
	*/
	return static_cast<float>(currentTicks);
}

float Timer::GetCurrentTickSec() const
{
	/*
	Dividing current ticks (in milliseconds) to milli_to_Sec variable which is 1000.

	No need for a static cast as we're doing a float division, it will automatically
	return a float value.
	*/
	return currentTicks / MILLI_TO_SEC;
}
