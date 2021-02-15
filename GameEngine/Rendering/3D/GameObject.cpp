#include "GameObject.h"

/*
Makes sure theres no jung data in the model varable.

Sets class' varable model, equal to model that we
pass in as a parameter.
*/
GameObject::GameObject(Model * model_) : model(nullptr)
{
	model = model_;
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

void GameObject::Render()
{
	/*
	 Checks to see if there'sa model associated with it.

	 To render the game object, we just call render on the model.
	*/
	if (model)
	{
		model->Render();
	}
}
