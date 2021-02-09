#include "Game1.h"


// When inheriting, make sure to declare the constructor of the parent class
Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr)
{
}


Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	/*
	Makes sure that the scene number starts out w/ a value of 0.

	If not, dont initalize.
	
	Return value of OnCreate is equal to return value of current
	scenes OnCreate function.
	*/
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate(); 
	}

	std::cout << "Engine's scene is not initialized to 0" << std::endl;
	return false;
}

void Game1::Update(const float deltaTime_)
{
	/*
	Makes sure that the game's current scene number matches the engine's
	current scene number.
	*/
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene())
	{
		BuildScene();
	}
	currentScene->Update(deltaTime_); // regardless of the outcome, update the current scene.
}

void Game1::Render()
{
	currentScene->Render(); // Renders the current scene
}

void Game1::BuildScene()
{
	/*
	Deletes all of the previous scenes objects &
	deallocate's its memory properly.
	*/
	delete currentScene;
	currentScene = nullptr;


	/*
	Switch based on the engine's current scene number.

	If the current engine's current scene number is = to 1, switch to the game scene.

	If the case is equal to 0, it's default, abd tge current scene is equal to start scene.

	Having a default scene is important, if others ask to switch to a scene you dont have,
	you have a default to catch those certain things.

	Note: Dont forget [break;]'s leave the switch statement and it will not continue on.
	*/
	switch (CoreEngine::GetInstance()->GetCurrentScene()) 
	{
	case 1:
		currentScene = new GameScene();
		break;
	default: //case 0:
		currentScene = new StartScene();
		break;
	}

	/*
	Set game's current scene number equal to the engines current scene number.

	Then, call to create the new current scene.
	
	Check's to see if the return value of the current OnCreate is equal to false,
	if so print out a line to the console, then call that new exit function.

	Reason why we call the Exit function is because the BuildScene function is a
	void function. We dont wan't this as a boolean because it's called inside 
	of update and update should not return anything.
	*/
	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate())
	{
		std::cout << "Scene failed to be created" << std::endl;
		CoreEngine::GetInstance()->Exit();
	}

}
