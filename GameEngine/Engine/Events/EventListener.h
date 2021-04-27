#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "MouseEventListener.h"

/*
	EventListener is seperated to 
	MouseEventListener since it
	essentially listens to all
	types of events. 

	EventListener helps with distinction
	of other types of events. Ex, if
	we do a mouse event, it goes to
	the mouse event listener class, if 
	it's keyboard go to keyboard.	
*/

class EventListener
{
public:

	// Purely static class
	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator=(const EventListener&) = delete;
	EventListener& operator=(EventListener&&) = delete;

	EventListener() = delete;
	~EventListener();

	/*
	 This update is not a normal update, it's
	 a special event listener update.
	*/
	static void Update();

};

#endif // !EVENTLISTENER_H




