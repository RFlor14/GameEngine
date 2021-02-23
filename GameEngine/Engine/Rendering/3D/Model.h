#ifndef MODEL_H
#define	MODEL_H

#include "Mesh.h"

class Model
{
public:
	/*
	Makes sure each model has the ability to secify what 
	shader program to sue to render itself.
	*/ 
	Model(GLuint shaderProgram_);
	~Model();

	void Render();
	
	// Adds a mesh to this model.
	void AddMesh(Mesh* mesh_);

private:
	
	// Holds a collection of mesh pointers.
	std::vector<Mesh*> meshes;

	// Saves the shader program
	GLuint shaderProgram;
};
#endif // !MODEL_H



