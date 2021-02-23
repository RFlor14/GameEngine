#include "GameScene.h"


// sets shape's default value to nullptr and makes sure it has no junk data.
GameScene::GameScene() : shape(nullptr){}


GameScene::~GameScene()
{
	// As always after creating a ptr, delete it.
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	// Quick Debug to see if everything is good
	Debug::Info("Game Scene created successfully", "GameScene.h", __LINE__);

	/*
	Sets up all vertices for the triangle.

	1) Create a vertex object [v]
	2) Create vertexList
	3) Reserve goes into memory, takes a block of memory, puts a reserve sign on it.
	   In this case, we're making a triangle, so 3 reserves.
	4) Fill's in the position of the vertex
	5) After setting up the position, push it back to the vertex list.

	[Quick Note]
	Since we created a vector of vertex objects that are non pointer, this gives
	us the ability of just creating the one vertex object, set up its position,
	then overwrite it.

	If we were to use a pointer, if you change the value of the pointer in one spot,
	it will change that value everywhere that pointer is used.
	*/

	// Triangle 1
	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(6);
	v.position = glm::vec3(0.25f, 0.25f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.25f, -0.25f, 0.0f);
	v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.25f, -0.25f, 0.0f);
	v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	// Triangle 2
	v.position = glm::vec3(-0.25f, -0.25f, 0.0f);
	v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.25f, 0.25f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.25f, 0.25f, 0.0f);
	v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	// Creates the model, pass in the GLuint for the shader program
	Model* model = new Model(ShaderHandler::GetInstance()->GetShader("colourShader"));

	// Set the model w/ a mesh
	model->AddMesh(new Mesh(vertexList));

	// Create the game object
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_){}

void GameScene::Render()
{
	shape->Render();
}
