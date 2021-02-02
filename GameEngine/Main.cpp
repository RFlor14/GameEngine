#include "Engine/Core/CoreEngine.h" // self explanatory, allows acess of entire Engine class

// Main Is now very basic, and will not be changed anymore in the forseeable future.
int main(int argc, char* argv[]) 
{

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
		std::cout << "Engine failed to initialize" << std::endl;
		return 0;
	}

	CoreEngine::GetInstance()->Run(); // Once engine is created, call run function.
	return 0;


}

