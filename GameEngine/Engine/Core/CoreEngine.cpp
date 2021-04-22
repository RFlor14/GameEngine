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

Sets fps to 60.

Sets gameInterface to null to make sure theres no junk data.

Sets current scene number to 0.
*/
CoreEngine::CoreEngine() : window(nullptr), isRunning(false), fps(60), gameInterface(nullptr), currentSceneNum(0) {} 

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
	/*
	It's static so, call Debug class, then scope resolution operator to OnCreate,
	which gives us acess to all of the public functions in it.
	*/
	Debug::OnCreate(); 

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
		Debug::FatalError("Window failed to initialize", "in CoreEngine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}

	// SETTING UP SHADER
	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");


	ShaderHandler::GetInstance()->CreateProgram("basicShader",
		"Engine/Shaders/VertexShader.glsl",
		"Engine/Shaders/FragmentShader.glsl");


	/*
	Checks if gameInterface exists.

	Inner if statement, is the same as the windows, checks if it works,
	if not, print out to console, clean up, then set isRunning to false.
	*/
	if (gameInterface)
	{
		if (!gameInterface->OnCreate()) 
		{
			Debug::FatalError("Game failed to initialize", "in CoreEngine.cpp", __LINE__);
			
			OnDestroy();
			return isRunning = false;
		}
	}


	/*
	Checks if debug class works.

	Reason why we're doing "x.cpp" is so that, it doesnt print out the full file path,
	easier to see which specific file has the problem.
	*/ 
	Debug::Info("Everything worked", "CoreEngine.cpp", __LINE__); 

	// Starts the timer, must be done before setting isRunning to true.
	timer.Start();

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
		timer.UpdateFrameTicks(); // Again, just updates previous and current ticks varables equal to.
		Update(timer.GetDeltaTime()); // Uses our GetDeltaTime function, instead of hardcoding
		Render();

		/*
		Stops the engine for as many millisec as we pass in.

		Passing in fps will dictate how much sleep time will need to be returned.
		*/
		SDL_Delay(timer.GetSleepTime(fps)); 
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

void CoreEngine::Exit()
{
	// Any time the engine is inside the while loop, it hops out of it, and starts shutting down everything.
	isRunning = false; 
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}

int CoreEngine::GetCurrentScene() const
{
	return currentSceneNum;
}

/*
 [static_cast] To getWidth and Height from the window class return an integer
 but we want a float.
*/
float CoreEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float CoreEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

void CoreEngine::SetGameInterface(GameInterface * gameInterface_)
{
	// sets gameInterface var equal to the pointer that gets passed in as a param to this function
	gameInterface = gameInterface_; 
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void CoreEngine::Update(const float deltaTime_) 
{
	/*
	Checks to see if gameInterface variable exists.

	If true, call update function on game interface.
	*/
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
		//std::cout << deltaTime_ << std::endl; // verifies if timer is working properly.
	}


	
}

void CoreEngine::Render()
{
	// Same thing from Main.cpp
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // Tell's OpenGL what color should be used when cleared. (R,G,B,A)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Tell's OpenGL to clear Color and Depth buffer bit.

	// Calls in game's render function, if gameInterface exists
	if (gameInterface)
	{
		gameInterface->Render();
	}

	//CALL GAME RENDER
	SDL_GL_SwapWindow(window->GetWindow());
}

// Deletes window variable
void CoreEngine::OnDestroy()
{
	// call in shader handler destroyer
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();

	/*
	Cleans up the pointer.

	Set it to nullptr.

	Note: Always destroy from the inside out.
	*/
	delete gameInterface;
	gameInterface = nullptr;

	delete camera;
	camera = nullptr;

	delete window;
	window = nullptr; 

	SDL_Quit(); // Quits SDL, when destroying an engine, close entire project.
	exit(0); // Exits whole program w/ exit code 0.
}
