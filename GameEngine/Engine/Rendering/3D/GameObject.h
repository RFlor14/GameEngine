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
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	std::string GetTag() const;
	BoundingBox GetBoundingBox() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);

private:

	// Holds a refferrence to its model.
	Model* model;

	/*
	 This is tied into game object so that when making
	 changes to an object, it only affects that, instead
	 of the actual model.
	*/
	unsigned int modelInstance;
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::string tag;

	BoundingBox boundingBox;
};

#endif // !GAMEOBJECT_H







