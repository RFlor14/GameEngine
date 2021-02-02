#include "CoreEngine.h"

/*
Since it's a static, it must be redeclared at the top of the engine. This goes with any other static vars.

Must start with signature/datatype (std::unique_ptr<CoreEngine>)
Then, specify the specific varable name of static var (CoreEngine::engineInstance)
Ten give it a default value, in this case it's just (nullptr)
*/
std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

/* 
Sets default value for window.
Makes sure that the engine is(NOT)Running.
*/
CoreEngine::CoreEngine() : window(nullptr), isRunning(false) {} 

CoreEngine::~CoreEngine() {}

// What gets called when you want to acess anything from the engine that's public.
CoreEngine * CoreEngine::GetInstance()
{
	/*
	Checks if any instance has been created before for this unique ptr.

	If not, and it's the first time the instance gets function has been called,
	then it's nullptr and reset with a new CoreEngine.

	This is what calls the core engine constructor.
	*/
	if (engineInstance.get() == nullptr)
	{
		engineInstance.reset(new CoreEngine);
	}

	return engineInstance.get(); // returns what that pointer is holding.
}

// Has the same parameters as Windows onCreate since it does call that function.
bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	//Before calling onCreate, makes sure that we are creating and initializing the window pointer.
	window = new Window();

	/*
	Calls window's onCreate function, check's what the return value of the function is.

	!window means that if it returns false, go through the if statement.
	Which basically prints out an error on console, cleans window.
	
	return isRunning does two things:
	1) Sets isRunning to false. 
	2) Returns the value of isRunning var.
	*/
	if (!window->OnCreate(name_, width_, height_))
	{
		std::cout << "Window failed to initialize" << std::endl;
		OnDestroy();
		return isRunning = false;
	}

	// If everything goes well, engines onCreate sets isRunning var to true.
	return isRunning = true;
}

/* 
Entire game loop of the engine. 
The game loop is "Update, render, update render" - Scott

[Key Info]
Update goes first because anything that involves physics (like motion & collision)
happens inside of the update function. 

Whenever something needs to be rendered, it makes sure that it's rendering w/ most
up to date information and date positions.


*/
void CoreEngine::Run()
{

	while (isRunning)
	{
		Update(0.016f); // Updates in 60fps (1/60 = 0.0167).
		Render();
	}

	/* 
	Makes it clear when on destroy is being called (the if statement is optional
	as it does the same thing w/o it.

	if isRunning = false, jump outside of while loop from Run function,
	and go to OnDestroy function.
	*/
	if (!isRunning)
	{
		OnDestroy();
	}

}

bool CoreEngine::GetIsRunning()
{
	return isRunning;
}

void CoreEngine::Update(const float deltaTime_) {}

void CoreEngine::Render()
{
	// Same thing from Main.cpp
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Tell's OpenGL what color should be used when cleared. (R,G,B,A)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Tell's OpenGL to clear Color and Depth buffer bit.

	//CALL GAME RENDER
	SDL_GL_SwapWindow(window->GetWindow());
}

// Deletes window variable
void CoreEngine::OnDestroy()
{
	delete window; // cleans up the pointer
	window = nullptr; // then set it to nullptr
	SDL_Quit(); // Quits SDL, when destroying an engine, close entire project.
	exit(0); // Exits whole program w/ exit code 0.
}
