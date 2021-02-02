#include "Engine/Core/CoreEngine.h" // self explanatory, allows acess of entire window class

CoreEngine* engine; // creates global engine pointer

// THIS IS JUST FOR TESTING PURPOSES
int main(int argc, char* argv[]) 
{
	engine = new CoreEngine(); // Initalizes engine variable

	// Sets name, width, and height of the window, seen in the parameters.
	// Again, just error checking, if everything fails clean memory by deleting window, and stop the function.
	if (!engine->OnCreate("Game 258 Engine", 800, 600)) 
	{
		delete engine;
		engine = nullptr;
		return 0;
	}

	engine->Run();

	// Afterwards, clean everything
	delete engine;
	engine = nullptr;
	return 0;

}

