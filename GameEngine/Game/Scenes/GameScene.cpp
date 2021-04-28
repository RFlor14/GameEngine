#include "GameScene.h"


// sets shape's default value to nullptr and makes sure it has no junk data.
GameScene::GameScene() {}


GameScene::~GameScene(){}

bool GameScene::OnCreate()
{
	// Quick Debug to see if everything is good
	Debug::Info("Game Scene created successfully", "GameScene.h", __LINE__);

	// Creates the camera
	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

	// Creates the light
	CoreEngine::GetInstance()->GetCamera()->AddLightSources(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate();

	//// Creates the model, pass in the GLuint for the shader program
	Model* diceModel = new Model("Resources/Models/Dice.obj",
	"Resources/Materials/Dice.mtl",
	ShaderHandler::GetInstance()->GetShader("basicShader"));

	Model* appleModel = new Model("Resources/Models/Apple.obj",
	"Resources/Materials/Apple.mtl",
	ShaderHandler::GetInstance()->GetShader("basicShader"));

	// test transform
	// model->SetScale(glm::vec3(0.5f));

	//Adds the model to the scene graph
	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);


	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(-2.0f, 0.0f, -2.0f)), "Dice");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(1.5f, 0.0f, 0.0f)),
		"Apple");

	diceModel = nullptr;
	appleModel = nullptr;

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
