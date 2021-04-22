#ifndef COREENGINE_H
#define COREENGINE_H


#include <memory> // Allows the acess of smart pointers.
#include "Window.h"
#include "Timer.h"
#include "Debug.h" // Added Debug
#include "GameInterface.h"
#include "Scene.h"

#include "../Rendering/SceneGraph.h"
#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"
#include "../Graphics/MaterialHandler.h"

#include "Camera.h"

class CoreEngine
{
public:

	/*
	Disables the creation of copy or move constructors. Ensures that no two objects are the same.

	This can be used for any class that you want, where you want to make sure
	no one can be able to use a copy or move constructor for it.

	Makes sure that if anyone tries to move or a copy constructor of this class, give out an error.
	*/
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	static CoreEngine* GetInstance(); // Returns an instance or refference to this core engine object.

	bool OnCreate(std::string name_, int width_, int height_); // Same parameter as window
	void Run(); // Doesn't return anything.
	void Exit();

	bool GetIsRunning() const; // Returns the value of isRunning variable.
	int GetCurrentScene() const; // scene number holder

	// For "Camera"
	float GetScreenWidth() const;
	float GetScreenHeight() const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_); // takes in an int for this new scene number
	void SetCamera(Camera* camera_);


private:

	/*
	As always, gotta have a constructor and deconstructor.
	Moved to private so no one can acess it for singleton pattern.
	*/
	CoreEngine();
	~CoreEngine();


	void Update(const float deltaTime_); // deltaTime_ MUST be constant float, makes sure that no one changes it!
	void Render(); // Everything that will be rendered to the screen will be in here.
	void OnDestroy(); // Very simple, deletes functions and cleans memory.

	/* 
	A type of smart pointer. Holds a pointer to the object you specify; a basket.
	Once it goes out of scope, deletes itself automatically.

	Must be told how to delete itself as it's private; i.e default_delete. default_delete
	must be set to a friend as it can see private things.
	*/
	static std::unique_ptr<CoreEngine> engineInstance; 
	friend std::default_delete<CoreEngine>;

	Window* window; // This is the window class that we created.
	bool isRunning; // Check's if engine "isRunning".

	Timer timer; // Timer instance
	unsigned int fps;

	GameInterface* gameInterface; // Creates game interface pointer.

	int currentSceneNum; // integer to represent the scene number

	Camera* camera;
};

#endif // !COREENGINE_H
