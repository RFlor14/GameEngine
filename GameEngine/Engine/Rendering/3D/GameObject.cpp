#include "GameObject.h"

/*
Makes sure theres no jung data in the model varable.

Sets class' varable model, equal to model that we
pass in as a parameter.
*/
GameObject::GameObject(Model * model_) : model(nullptr), position(glm::vec3()),
angle(0.0f), rotation(glm::vec3(0.0f,1.0f,0.0f)), scale(glm::vec3(1.0f)), modelInstance(0)
{
	model = model_;

	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr), position(glm::vec3()),
angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)), modelInstance(0)
{
	model = model_;
	position = position_;

	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::~GameObject()
{
	/*
	Reason why it's in an [if] is we want our engine to have
	the ability to have an empty game object, meaning sometimes
	it might not have a model associated to it.

	Check's if the model actually exists, delete the pointer.
	*/
	if (model)
	{
		delete model;
	}
	
	//Regardless if it equals null or not, set it equal to null.
	model = nullptr;
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);
}

void GameObject::Render(Camera* camera_)
{
	/*
	 Checks to see if there'sa model associated with it.

	 To render the game object, we just call render on the model.
	*/
	if (model)
	{
		model->Render(camera_);
	}
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetAngle() const
{
	return angle;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

std::string GameObject::GetTag() const
{
	return tag;
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}
