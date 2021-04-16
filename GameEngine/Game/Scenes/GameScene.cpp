#include "GameScene.h"


// sets shape's default value to nullptr and makes sure it has no junk data.
GameScene::GameScene() : shape(nullptr), model(nullptr){}


GameScene::~GameScene()
{
	// As always after creating a ptr, delete it.
	model = nullptr;
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	// Quick Debug to see if everything is good
	Debug::Info("Game Scene created successfully", "GameScene.h", __LINE__);

	// Creates the camera
	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

	// Creates the light
	CoreEngine::GetInstance()->GetCamera()->AddLightSources(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)));

	//// Creates the model, pass in the GLuint for the shader program
	model = new Model("Resources/Models/Dice.obj",
	"Resources/Materials/Dice.mtl",
	ShaderHandler::GetInstance()->GetShader("basicShader"));

	// test transform
	// model->SetScale(glm::vec3(0.5f));

	// Create the game object
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	shape->Update(deltaTime_);
}

void GameScene::Render()
{
	shape->Render(CoreEngine::GetInstance()->GetCamera());
}
