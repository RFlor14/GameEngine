#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>


/*
Defines magic numbers as constant values.

Can be done in two ways:
1) #define // Issue is it doesn't take any place in memory, getting its adress
can go bad. This uses the preprocessor which is not set up for doing these tasks.
Usually use #define if you have a # if statement.

2) constexpr // Specifically defining it as a float w/ a name that is equal to something.
*/
constexpr float MILLI_TO_SEC = 1000.0f; 

class Timer
{
public:

	/* 
	Same as CoreEngine, restricts ability from copying and moving constructors 
	of this instance of timer.
	*/
	Timer(const Timer&) = delete;
	Timer(Timer &&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	Timer();
	~Timer();

	void Start(); // Initialize function.
	void UpdateFrameTicks(); // Updates current and previous tick value.

	// All constant as a promise not to change them. 
	float GetDeltaTime() const; // Gets the time between current and previous frame.
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTickMilli() const;
	float GetCurrentTickSec() const;


private:

	// Unsigned as time is never negative, these ticks can jump to a very large number.
	unsigned int prevTicks;
	unsigned int currentTicks;
};

#endif // !TIMER_H
