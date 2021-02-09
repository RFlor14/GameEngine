#include "StartScene.h"



StartScene::StartScene()
{
}


StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	Debug::Info("start scene", "StartScene.cpp", __LINE__);

	return true; // have it return to true so the program can run
}

void StartScene::Update(const float deltaTime_)
{
	if (SDL_PollEvent(&event)) {
		switch (event.key.keysym.sym) {
		case SDLK_1:
			CoreEngine::GetInstance()->SetCurrentScene(1);
			break;
		default:
			break;
		}
	}
}

void StartScene::Render()
{
}
