#ifndef MODEL_H
#define	MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

class Model
{
public:

	/*
	Give all params default value so when it's needed to be updated,
	there's no errors because it assumes you're using a default value.

	[shaderProgram_] makes sure each model has the ability to specify what
	shader program to use to render itself.
	*/
	Model(GLuint shaderProgram_, glm::vec3 position_ = glm::vec3(),
		float angle_ = 0.0f, 
		glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3 scale_ = glm::vec3(1.0f));

	~Model();

	void Render(Camera* camera_);
	
	// Adds a mesh to this model.
	void AddMesh(Mesh* mesh_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;


	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);


private:
	
	// Holds a collection of mesh pointers.
	std::vector<Mesh*> meshes;


	// Saves the shader program
	GLuint shaderProgram;


	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;


	// returns a 4x4 matrix
	glm::mat4 GetTransform() const;


};
#endif // !MODEL_H



