#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string> // allows us to use type string.
#include <iostream> // allows us to use [std].

class Window 
{
public:
	Window(); // constructor
	~Window(); // destructor

	/* name with _ at the end because there are some system 
	variables that has an _, which you shouldn't touch.
	
	Also lets you know that it's a parameter, also lets you do things like
	width = width_ vs this->width = width_*/
	bool OnCreate(std::string name_, int width_, int height_); 

	void OnDestroy(); // cleans memory by destroying

	/* Const @ end lets you return a normal int. It's basically a promise
	that you won't change any variables inside the function.*/
	int GetWidth() const; 
	int GetHeight() const;
	SDL_Window* GetWindow() const;

private:

	// Sets OpenGL attributes before and after creating a window.
	void SetPreAttributes();
	void SetPostAttributes();

	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext context; // Lets SDL and OpenGL to communicate w/ our GPU
};

#endif // !WIDNOW_H
