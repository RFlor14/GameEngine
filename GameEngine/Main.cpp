#include "Engine/Core/Window.h" // self explanatory, allows acess of entire window class

Window* window; // creates global window pointer

// THIS IS JUST FOR TESTING PURPOSES
int main(int argc, char* argv[]) 
{
	window = new Window(); // calls in OnCreate constructor

	// Sets name, width, and height of the window, seen in the parameters.
	// Again, just error checking, if everything fails clean memory by deleting window, and stop the function.
	if (!window->OnCreate("Game 258 Engine", 800, 600)) 
	{
		delete window;
		window = nullptr;
		return 0;
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Tell's OpenGL what color should be used when cleared. (R,G,B,A)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Tell's OpenGL to clear Color and Depth buffer bit.
	// >-< this line is where rendering happens.
	SDL_GL_SwapWindow(window->GetWindow());  
	SDL_Delay(5000); // How long the window's chilling in the screen (5s)

	// Afterwards, clean everything
	delete window;
	window = nullptr;
	return 0;

}

