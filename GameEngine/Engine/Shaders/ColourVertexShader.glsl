#version 450 core

/*
Because of the vertex object, vertex shader gets all of its
data from VAO and VBO [layout]

This is kind of the same as the Mesh.cpp's getAttrib.

The [order and data] must be the same as the attributes enabled in
the generate buffers function.

It deals with setting the position of the vertex.
*/
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 Normal;
out vec2 TexCoords;
out vec3 Colour; // currently we're just using this

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	/*
	[gl_Position] = keyword specific to vertex shaders,
	this tells OpenGL what the vertex position should be.
	*/
	gl_Position = projection * view * model * vec4(position, 1.0f);

	// sets out colour to in colour
	Colour = vec3(1.0f);
}