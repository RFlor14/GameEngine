#include "EventListener.h"
#include "../Core/CoreEngine.h"

EventListener::~EventListener()
{
}

// Called Every frame
void EventListener::Update()
{
	/*
	 Ever frame, create a new sdl event.

	 Then, poll the events that are
	 currently happening in this instance
	 of the engine.
	*/
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		/*
		 First, check that, if the event type 
		 is a quit, call the engines exit
		 function.
		*/
		if (sdlEvent.type == SDL_QUIT)
		{
			CoreEngine::GetInstance()->Exit();
		}

		/*
		 If it's not a quite type, go into the
		 switch case statement.

		 Cases are listed one after the other
		 because if this value of this type is either
		 any of these, then call in mouse event's
		 update function.
		*/
		switch (sdlEvent.type)
		{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			MouseEventListener::Update(sdlEvent);
			break;
		default:
			break;
		}
	}
}
