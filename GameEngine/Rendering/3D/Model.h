#ifndef MODEL_H
#define	MODEL_H

#include "Mesh.h"

class Model
{
public:
	Model();
	~Model();

	void Render();
	
	// Adds a mesh to this model.
	void AddMesh(Mesh* mesh_);

private:
	
	// Holds a collection of mesh pointers.
	std::vector<Mesh*> meshes;
};
#endif // !MODEL_H



