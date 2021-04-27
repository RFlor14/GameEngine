#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

// Redeclare static variables
CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::ivec2 MouseEventListener::mouse = glm::ivec2();
glm::ivec2 MouseEventListener::prevMouse = glm::ivec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisteringEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)
{
	/*
	 Depending on the event, find out the
	 event type, then depeinding on the 
	 event type, call a different function.
	*/

	if (e_.type == SDL_MOUSEBUTTONDOWN)
	{
		UpdateMousePosition();
		NotifyOfMousePressed(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEBUTTONUP)
	{
		UpdateMousePosition();
		NotifyOfMouseReleased(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEMOTION)
	{
		UpdateMousePosition();
		NotifyOfMouseMoved();
	}
	else if (e_.type == SDL_MOUSEWHEEL)
	{
		UpdateMousePosition();
		NotifyOfMouseScroll(e_.wheel.y);
	}

}

void MouseEventListener::NotifyOfMousePressed(int buttonType_)
{
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_)
{
}

void MouseEventListener::NotifyOfMouseMoved()
{
}

void MouseEventListener::NotifyOfMouseScroll(int y_)
{
}

glm::ivec2 MouseEventListener::GetPreviousMousePosition()
{
	return prevMouse;
}

glm::ivec2 MouseEventListener::GetMousePosition()
{
	return mouse;
}

glm::ivec2 MouseEventListener::GetMouseOffset()
{
	 /*
	 [important] for Y,

	 We're doing the previouse first vs
	 the current position, as we want
	 the range from the top to bottom.

	 prev - current also makes it go
	 0 at the bottom of the screen, since 
	 SDL makes it 0 at the top.
	*/
	return glm::ivec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition()
{
	int tmpX, tmpY;

	/*
	 We passing in by reference, means
	 that the [SDL_GetMouseState] will
	 actually change the value of
	 these integers.

	 After the function is called,
	 the tmpX and tmpY will have
	 the value of the  new mouse position.
	*/
	SDL_GetMouseState(&tmpX, &tmpY);
	
	/*
	 Change in tmpY helps with setting 0
	 to the bottom of the screen.

	 Take screen height minus the tempY
	 position.
	*/
	tmpY = static_cast<int>(engineInstance->GetScreenHeight()) - tmpY;

	// Updates mouse position.
	if (firstUpdate)
	{
		prevMouse.x = mouse.x = tmpX;
		prevMouse.y = mouse.y = tmpY;
		firstUpdate = false;
	}
	else
	{
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tmpX;
		mouse.y = tmpY;
	}
}
