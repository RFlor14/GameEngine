#ifndef MESH_H
#define MESH_H

#include <glew.h> // Acess to all OpenGL API
#include <vector> // Dynamically sized Array, it essentially goes into memory
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // Allows to get the pointer of a specific glm variable type.


#include "../../Core/Camera.h"
#include "../../Graphics/MaterialHandler.h"

/*
[Non interleaved] - struct is created for all of the vertex attributes.

[glm]'s math data types are all inside of glm namespace, to acess it
we have to add [::]

[textureCoordinates] is a vec2, what place on a 2D image does the vertex
taxe its texture from.

[colour] not a standard vertex attribute, for now it's just to colour
the triangle. Vec3 which means RGB colour values.
*/
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates; 
};

struct SubMesh
{
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};

class Mesh
{
public:
	/*
	Constructor has a parameter, which is taking in a vector of type vertex.
	It's taking in (vector/list) of vertex objects.

	[&] means this vector is being passed in by refferrence as instead to
	being passed in by value. 
	
	Advantage of [&] is you can treat this parameter object as just a 
	normal, non pointer object; safer way.

	Reason why is a vector can be a really big object. 
	Passing it in by [value] can take a lot of computation time.
	Passing it in by [refferrence] is just passing the adress of
	the vector. 
	*/
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4>& instances_);

private:

	void GenerateBuffers(); // Sets up VAO and VBO.

	/*
	OpenGL unsigned int, that represents the VAO and VBO. 

	Creating as [GLuint] is like creating them using a pointer.
	It acts as the index value for what you've created.

	[VAO] = Vertex Array Object
	Object that states to the GPU how we store our vertex data.

	[VBO] = Vertex Buffer Objects
	Object buffer that provides the methods to push data to the GPU.
	*/
	GLuint VAO, VBO; 

	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc, 
		viewPosLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, 
		lightSpecularLoc, lightColourLoc;
};
#endif // !MESH_H



