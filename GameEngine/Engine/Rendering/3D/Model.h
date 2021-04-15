#ifndef MODEL_H
#define	MODEL_H

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"

class Model
{
public:

	/*
	Give all params default value so when it's needed to be updated,
	there's no errors because it assumes you're using a default value.

	[shaderProgram_] makes sure each model has the ability to specify what
	shader program to use to render itself.
	*/
	Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	~Model();

	void Render(Camera* camera_);
	
	// Adds a mesh to this model.
	void AddMesh(Mesh* mesh_);

	
	// Takes in pos, ang, rot, sca and creates a model matrix.
	unsigned int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);

	/* 
	 Takes in a specific index of an instance (pos, ang...) then it goes to
	 the vector of modelInstances and update that specific instances model matrix.
	*/
	void UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	
	/*
	 You pass it the specific index of the instance, then it returns 
	 the instances model matrix.
	*/ 
	glm::mat4 GetTransform(unsigned int index_) const;

private:
	
	// creates the transformation matrix, takes in (pos, ang...)'s values to create that matrix.
	glm::mat4 CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	
	void LoadModel();

	// Holds a collection of mesh pointers.
	std::vector<Mesh*> meshes;

	// Saves the shader program
	GLuint shaderProgram;

	/*
	 Holds a vector for all of the model's instances, and returns
	 the number of the current or newly created instances.
	*/
	std::vector<glm::mat4> modelInstances;

	LoadOBJModel* obj;

};
#endif // !MODEL_H



