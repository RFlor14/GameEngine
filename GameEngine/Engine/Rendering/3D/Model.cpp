#include "Model.h"

// Constructor sets up the meshes vector to be an empty vector.
Model::Model(GLuint shaderProgram_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
	: meshes(std::vector<Mesh*>()), shaderProgram(0), position(glm::vec3()), angle(0.0f), 
	rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f))
{
	// set shader program var to what we passed in as a param.
	shaderProgram = shaderProgram_;

	position = position_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;
}

/*
 Where the list of pointers comes into play.

 As supposed to mesh destructor, we actually have
 to go through each element of this meshes vector.

 for each element inside of the vector, we have to
 delete it and then set it to nullptr.

 (Every single pointer in here gets proplerly deleted,
 and its memory is deallocated.)
*/
Model::~Model()
{
	/*
	[if] Checks to see if meshes have something in it.

	[for each loop] kinda the same thing as the regular for loop we know,
	although this creates [m] a temporary local variable for each element,
	and for each itteration go to the next element inside of the vector.

	[auto] = automatically set the signature type of this variable.
	[:] = keyword in. For each element in this meshes vector, we do....
	delete, then set it to nullptr.
	*/
	if (meshes.size() > 0)
	{
		for (auto m : meshes)
		{
			delete m;
			m = nullptr;
		}

		// Now that every object is null, clear this meshes vector.
		meshes.clear();
	}
}

void Model::Render(Camera* camera_)
{
	/*
	[glUseprogram] = tells OpenGL to switch the shader program to
	a specific shader program that we pass it in.

	I.e. this model uses this specific shader program.
	*/
	glUseProgram(shaderProgram);

	/*
	For each mesh inside of the meshes list, call render.

	The role of the Model as parent is to basically just
	tell model to render its child meshes.
	*/
	for (auto m : meshes)
	{
		m->Render(camera_, GetTransform());
	}
}

// Adds a mesh to the meshes vector.
void Model::AddMesh(Mesh * mesh_)
{
	/*
	[push_back] will append an element, adding it to the very
	end of the list.
	*/
	meshes.push_back(mesh_);
}

/*
Creates a model matrix (contains all of the models transformations).

[glm] enables acess to translate, rotate, and scale.
[rotate] is the axis of rotation, [0, 1, 0] rotation happens in y-axis.
*/
glm::mat4 Model::GetTransform() const
{
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotation);
	model = glm::scale(model, scale);
	return model;
}

glm::vec3 Model::GetPosition() const
{
	return position;
}

float Model::GetAngle() const
{
	return angle;
}

glm::vec3 Model::GetRotation() const
{
	return rotation;
}

glm::vec3 Model::GetScale() const
{
	return scale;
}

void Model::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void Model::SetAngle(float angle_)
{
	angle = angle_;
}

void Model::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
}

void Model::SetScale(glm::vec3 scale_)
{
	scale = scale_;
}



