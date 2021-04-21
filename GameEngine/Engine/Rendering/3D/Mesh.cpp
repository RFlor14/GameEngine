#include "Mesh.h"

/*
Sets up the class' vertex list equal to the parameter that gets passed in.

[VBO] and [VAO]'s default values are set to 0. Since it's an unsigned int,
lowest it can go is 0.

Sets [vertexList] to equal an empty vector. When creating an empty vector it's
vector name equal to the signature of the vetor followed by empty brackets.
*/ 
Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0),
shaderProgram(0), modelLoc(0), viewLoc(0), 
projectionLoc(0), textureLoc(0), viewPosLoc(0), lightPosLoc(0),
lightAmbientLoc(0), lightDiffuseLoc(0), lightSpecularLoc(0),
lightColourLoc(0)
{
	/*
	MUST happen before [GenerateBuffers].

	We're setting the class' vertex list equal to the vertex
	that we get passed in as a parameter.
	*/
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	/*
	Deletes [VAO] and [VBO], we're doing it this way because
	OpenGL has its own way of deleting them.

	Passes in how many [VAO] or [VBO] you want to delete. In
	this case [1].
	*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	/*
	Since it holds non pointer objects, we don't have to go
	through the vector and delete every single object.
	*/
	if (subMesh.vertexList.size() > 0)
	{
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0)
	{
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_,  std::vector<glm::mat4>& instances_)
{
	// Render everything needed for the texture first.
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

	// Render Light
	glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetLightPos()));
	glUniform1f(lightAmbientLoc, camera_->GetLightSources()[0]->GetAmbient());
	glUniform1f(lightDiffuseLoc, camera_->GetLightSources()[0]->GetDiffuse());
	glUniform1f(lightSpecularLoc, camera_->GetLightSources()[0]->GetSpecular());
	glUniform3fv(lightColourLoc, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetLightColour()));

	/*
	 [glUniformMatrix4fv] Set the model matrix variable (set a 4x4 matrix var).
	 - [f] setting up float
	 - [v] setting it by a pointer

	 Parameters:
	 1) actual location of the uniform we want to set
	 2) what is the count of how many uniforms you're setting. (1, since one matrix)
	 3) transpose matreix? no
	 4) actual pointer to the matrix

	 [view] pass in getview param
	 [project] pass in perpspective param since we're doing 3D
	*/
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));


	//First thing to always do w/ render is to bind the class' [VAO].
	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST); // Enables depth test, when objects are rendered, Z value is taken into account.

	/*
	 For each instance, we need to draw the mesh.

	 Instead of passing in the transform matrix, we're
	 passing in the specific instance that we're iterating over.

	 Then call to draw the triangles.
	*/
	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	/*
	Call to draw for OpenGL, in this case we're drawing arrays

	1st param = render type, how we want the data to be rendered.

	2nd param = start of the array

	3rd param = size of the array.

	[GL_TRIANGLES] = an OpenGL render type. OpenGL will take groups
	of 3 vertices and create a triangle out of them.
	
	Some other render types are (GL_POINTS, GL_LINES, GL_LINE_STRIP, and more).
	*/ 

	// Clears vertex array for future use.
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	/*
	1-2) Generate [VAO] and [VBO], pass in their refference. 
	Since we only make [1] of each, we pass [1] as the first
	parameter of the two functions.

	3) Binds VBO as an array buffer. Reason to bind it is it's
	like opening a closet, we're going to put a lot of data in there,
	then later on we're gonna close the door that closet.

	4) To fill in [VBO Data] we use [glBufferData]
	1st param = type of buffer

	2nd param = size of the array // [.size()] gets you the
	size of the vector then multiplied by the byte size of 
	each vertex element.
	
	3rd param = adress of the first item in the array. By doing
	it this way, we're assuming that this vertex list is filled in.

	4th param = [GL_STATIC_DRAW] means data will only be changed once.
	*/
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex),
		&subMesh.vertexList[0], GL_STATIC_DRAW);

	/*
	Whenever we tell the GPU what attribute is going to be
	in the VAO and VBO set, we MUST always enable vertex attrib array.

	[glVertexAttribPointer] tells the GPU how things are seperated.

	1st param = location of the attributes.

	2nd param = size of vertex attribute. It's the position, which is vec3.

	3rd param = type of data. 2nd + 3rd param = this specific vertex attribute
	will have 3 float values associated with it.

	4th param = do we want data to be normalized (we dont, hence false).

	5th param = specify space between consecutive vertex attribute sets.
	If we're looking at a triangle, there's 3 vertices. When GPU looks at
	position, this tells it, if you want the the first vert, its here. To
	get position of next vert, jump this many bytes.

	6th param = looks at the very first attribute of the structure.
	In this case at the start it's 0, then we offset it.
	*/

	// POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
		(GLvoid*)offsetof(Vertex, normal));

	// TEXTURE COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, textureCoordinates));


	/*
	 Binds vertex array and the buffer to 0.

	 Essentially, we're closing the doors. It also
	 ensures that no one can mess with the 
	 [VBO] and [VAO] data.
	*/
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*
	 Note: 
	 The location will never change throughout the programs lifetime.
	 The string you pass in [model] has to match exactly to what
	 is in the shader.

	 1) Get the location for the uniform when generating the buffers.
	 2) save it to our variable.
	 3) use that variable when we want to set the unform's value.

	*/
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	// Camera and Light
	viewPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightSpecularLoc = glGetUniformLocation(shaderProgram, "light.specular");
	lightColourLoc = glGetUniformLocation(shaderProgram, "light.lightColour");
}
