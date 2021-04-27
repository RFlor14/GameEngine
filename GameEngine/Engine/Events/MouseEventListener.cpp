#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::ivec2 MouseEventListener::mouse = glm::ivec2();
glm::ivec2 MouseEventListener::prevMouse = glm::ivec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
}

void MouseEventListener::RegisteringEngineObject(CoreEngine* engine_)
{
}

void MouseEventListener::Update(SDL_Event e_)
{
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
	return glm::ivec2();
}

glm::ivec2 MouseEventListener::GetMousePosition()
{
	return glm::ivec2();
}

glm::ivec2 MouseEventListener::GetMouseOffset()
{
	return glm::ivec2();
}

void MouseEventListener::UpdateMousePosition()
{
}
