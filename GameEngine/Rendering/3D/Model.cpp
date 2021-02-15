#include "Model.h"

// Constructor sets up the meshes vector to be an empty vector.
Model::Model() : meshes(std::vector<Mesh*>()){}

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
		meshes.clear;
	}
}

void Model::Render()
{
	/*
	For each mesh inside of the meshes list, call render.

	The role of the Model as parent is to basically just
	tell model to render its child meshes.
	*/
	for (auto m : meshes)
	{
		m->Render();
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



