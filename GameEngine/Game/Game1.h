#ifndef GAME1_H
#define GAME1_H

/*
[../] allows you to jump out of the current folder and go
somewhere else, in this case the parent folder.
*/
#include "../Engine/Core/CoreEngine.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

// Publicly inherting GameInterface
class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();

	/*
	override is a compile time check, which will verify the signature of
	the functions and verify that they match.
	*/
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;

private:
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();
};



#endif // !GAME1_H
