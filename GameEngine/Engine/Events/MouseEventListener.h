#ifndef MOUSEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <SDL.h>
#include <glm/glm.hpp>

/*
 Forward declerating the header,

 We need to include the core engine header,
 although eventually the MouseEventListener will
 be included int he engine.

 We're also using it here because we're
 using object type [CoreEngine* engine]. 
*/
class CoreEngine; 
class MouseEventListener 
{
public: 
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	MouseEventListener() = delete;
	~MouseEventListener();

	static void RegisteringEngineObject(CoreEngine* engine_);
	static void Update(SDL_Event e_);

	/*
	 We have four different functions as,
	 we will be doing a different thing depending 
	 on what function it is.
	*/
	static void NotifyOfMousePressed(int buttonType_);
	static void NotifyOfMouseReleased(int buttonType_);
	static void NotifyOfMouseMoved();
	static void NotifyOfMouseScroll(int y_);

	static glm::ivec2 GetPreviousMousePosition();
	static glm::ivec2 GetMousePosition();
	static glm::ivec2 GetMouseOffset();

private:
	/*
	 Refference to the engine instance
	 since we're using an register
	 engine object function.
	*/
	static CoreEngine* engineInstance;
	static glm::ivec2 mouse, prevMouse;

	/*
	 Just a boolean to check if it's the first
	 time things update.
	*/
	static bool firstUpdate;

	/*
	 Gets new mouse position, then
	 setting the previous mouse position
	 to current, then current to new.
	*/
	static void UpdateMousePosition();
};

#endif // !MOUSEVENTLISTENER_H