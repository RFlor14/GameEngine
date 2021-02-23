#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

/*
--Note--
Fragment shaders always have to have an out vec4 var.
From the pipeline, fragment shader is where we colour
everything in and where we pass the colored pixels
to all the test blends.
*/
out vec4 fColour;

/*
Set out [fColour] = whatever is our (in) color variable,
since it's a vec4, last param = 1.
*/
void main()
{
	fColour = vec4(Colour, 1.0);
}