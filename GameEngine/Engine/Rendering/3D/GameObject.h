#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:

	/*
	Important to use [star notation] here because it gives us
	the ability to create a game object, or an empty game object.

	If we want an empty game object, we just pass in nullptr.
	*/
	GameObject(Model* model_);
	~GameObject();

	void Render(Camera* camera_);
private:

	// Holds a refferrence to its model.
	Model* model;
};

#endif // !GAMEOBJECT_H







