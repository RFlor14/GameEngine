#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory> //Singleton
#include <unordered_map>
#include <map>
#include <vector>
#include "3D/GameObject.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();
	void OnDestroy();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* go_, std::string tag_ = "");
	GameObject* GetGameObject(std::string tag_);

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	/*
	 When adding objects to an unordered map, when you get all the objects in that map,
	 they might necessarily be in the same order tha tyou insert them. 
	 
	  Ex, Element 1,2,3 - when searching through it you might get Element 2,3,1

	 Reason why we use/might use them is because we dont care about the order of the 
	 elements, which means that insertion into the unordered map is much quicker.
	*/
	static std::unordered_map<GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;
};

#endif // !SCENEGRAPH_H

