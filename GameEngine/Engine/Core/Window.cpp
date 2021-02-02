#include "Window.h"

Window::Window() : window(nullptr), context(nullptr){} // another way of (window = nullptr, context = nullptr)

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	/* 
	FIRST THING! = Initalize SDL
	This also check's if everything's good, anything less than 0 will print
	out an error in the console = it didn't work!
	*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to iniialize SDL" << std::endl;
		return false; // This basically stops from continuing the OnCreate function.
	}

	/* 
	Everything clear? save width and height of window (equal to the parameter of OnCreate)
	No need to do "this->" although just incase.
	*/
	this->width = width_;
	this->height = height_;

	SetPreAttributes(); //calls in PreAttribute function

	/*
	Creates the window w/ the parameters given, then return refference of window.

	Parameters:
	1st = Title of window, convert string to const char*, () are needed as it's a function.
	2nd & 3rd = Defines x & y. Launches the window to center of screen .
	4th param = Lets SDL know to expect any OpenGL rendering to happen when creating a window.
	*/
	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);

	/*
	Again just an error check, if so, print to console and stop the function.
	!window is basiclaly just [window == nullptr], and it works with pointers.
	*/
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		return false;
	}

	// Allows OpenGL to be used in our engine; context is just a doorway to communicate to GPU.
	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	/*
	Initalizes GLEW library, returns an enum.
	If enum doesn't give out a value of GLEW_OK, print out the error, and stop the function.
	*/
	GLenum err = glewInit(); 
	if (err != GLEW_OK)
	{
		std::cout << "Failed to initalize GLEW" << std::endl;
		return false;
	}


	glEnable(GL_DEPTH_TEST); // Enables depth test, when objects are rendered, Z value is taken into account.
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; // Prints out OpenGL version.

	/*
	Everything worked properly.
	TIP: always have a return statement if you have a function that returns a type of data (bool, int, float)
	*/
	return true; // Everything worked properly!

}

void Window::OnDestroy()
{
	// Essentially just closes the door; i.e cleans up memory
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);

	/* No nede to do delete as This is a special pointer 
	of type SDL_Window, which has it's own destroying function */
	window = nullptr; 

}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;

}

SDL_Window * Window::GetWindow() const
{
	return window;
}

void Window::SetPreAttributes()
{
}

void Window::SetPostAttributes()
{
}
