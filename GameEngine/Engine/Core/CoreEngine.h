#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"

class CoreEngine
{
public:

	// As always, gotta have a constructor and deconstructor
	CoreEngine();
	~CoreEngine();

	bool OnCreate(std::string name_, int width_, int height_); // Same parameter as window
	void Run(); // Doesn't return anything.
	bool GetIsRunning(); // Returns the value of isRunning variable.

private:

	void Update(const float deltaTime_); // deltaTime_ MUST be constant float, makes sure that no one changes it!
	void Render(); // Everything that will be rendered to the screen will be in here.
	void OnDestroy(); // Very simple, deletes functions and cleans memory.
	Window* window; // This is the window class that we created.
	bool isRunning; // Check's if engine "isRunning".
};

#endif // !COREENGINE_H
