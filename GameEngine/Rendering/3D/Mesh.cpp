#include "Mesh.h"

/*
Sets up the class' vertex list equal to the parameter that gets passed in.

[VBO] and [VAO]'s default values are set to 0. Since it's an unsigned int,
lowest it can go is 0.

Sets [vertexList] to equal an empty vector. When creating an empty vector it's
vector name equal to the signature of the vetor followed by empty brackets.
*/ 
Mesh::Mesh(std::vector<Vertex>& vertexList_) : VAO(0), VBO(0), vertexList(std::vector<Vertex>())
{
	/*
	MUST happen before [GenerateBuffers].

	We're setting the class' vertex list equal to the vertex
	that we get passed in as a parameter.
	*/
	vertexList = vertexList_;

	/*
	
	*/
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
	through th vector and delete every single object.
	*/
	vertexList.clear(); 
}

void Mesh::Render()
{
	
	//First thing to always do w/ render is to bind the class' [VAO].
	glBindVertexArray(VAO);

	/*
	Call to draw for OpenGL, in this case we're drawing arrays

	1st param = render type, how we want the data to be rendered.

	2nd param = start of the array

	3rd param = size of the array.

	[GL_TRIANGLES] = an OpenGL render type. OpenGL will take groups
	of 3 vertices and create a triangle out of them.
	
	Some other render types are (GL_POINTS, GL_LINES, GL_LINE_STRIP, and more).
	*/ 
	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());

	// Clears vertex array for future use.
	glBindVertexArray(0);
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
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex),
		&vertexList[0], GL_STATIC_DRAW);

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

	// COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, colour));

	/*
	Binds vertex array and the buffer to 0.

	Essentially, we're closing the doors. It also
	ensures that no one can mess with the 
	[VBO] and [VAO] data.
	*/
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}