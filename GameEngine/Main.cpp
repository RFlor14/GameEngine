#include "Engine/Core/CoreEngine.h" // self explanatory, allows acess of entire Engine class
#include "Game/Game1.h"

// Main Is now very basic, and will not be changed anymore in the forseeable future.
int main(int argc, char* argv[]) 
{
	/*
	Set gameinterface to be a new pointer/object of this Game1 class.

	Call this before OnCreate since OnCreate calls the game interface's OnCreate.

	*/ 
	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	/*
	Sets name, width, and height of the window, seen in the parameters.
	gain, just error checking, if everything fails clean memory by deleting window, and stop the function.

	All it does now is it creates the game and engine. It then tell's the engine to go.

	Now we need call get instance first.

	GetInstance: 
	Is a function, () needed.
	Returns a CoreEngine pointer, -> needed, to acess any variables that are public.
	*/
	if (!CoreEngine::GetInstance()->OnCreate("Game 258 Engine", 800, 600)) 
	{
		Debug::FatalError("Engine failed to initialize", "Main.cpp", __LINE__);

		return 0;
	}

	CoreEngine::GetInstance()->Run(); // Once engine is created, call run function.
	return 0;


}

