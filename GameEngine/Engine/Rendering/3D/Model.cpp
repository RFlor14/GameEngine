#include "Model.h"

// Constructor sets up the meshes vector to be an empty vector.
Model::Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) :
	meshes(std::vector<Mesh*>()), shaderProgram(0), modelInstances(std::vector<glm::mat4>())
{
	// set shader program var to what we passed in as a param.
	shaderProgram = shaderProgram_;

	meshes.reserve(10);
	modelInstances.reserve(5);
	obj = new LoadOBJModel();
	obj->LoadModel(objPath_, matPath_);
	LoadModel();
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

	if (modelInstances.size() > 0)
	{
		modelInstances.clear();
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
		m->Render(camera_, modelInstances);
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

unsigned int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	/*
	 First, it creates a transform matrix based on the param
	 that it gets passed in.

	 Then it pushes it into the model instances vector.

	 Then it returns the size of the vector -1.
	 (-1 to make sure the instance that's saved in the game
	 object starts at 0).

	 If we have a vector that has two elements, size will return two.
	 If we create a new instance, (third element to the vector), 
	 size will return three, but the actual index of that third element is two.
	*/
	modelInstances.push_back(CreateTransform(position_, angle_, rotation_, scale_));
	return modelInstances.size() - 1;
}

void Model::UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index_] = CreateTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(unsigned int index_) const
{
	/*
	 Goes into model instances vector and returns the transform 
	 matrix associated with this specific index.
	*/ 
	return modelInstances[index_];
}

/*
 Similar to old Get Transform, this creates the
 transformation matrix, but now we're using the glm functions.
*/
glm::mat4 Model::CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);
	return model;
}


void Model::LoadModel()
{
	/*
	 Once the class loads in all the data, place it in sub meshes.

	 Go through all sub meshes, and for each sub mesh, add it
	 to the model's meshes vector.
	*/
	for (int i = 0; i < obj->GetSubMeshes().size(); i++)
	{
		meshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}
	 
	delete obj;
	obj = nullptr;

}







