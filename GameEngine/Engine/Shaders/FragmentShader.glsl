#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

// Enables the use as a 2D texture image.
uniform sampler2D inputTexture;

out vec4 fColour;

// Added light struct (week 7)
struct Light
{
	vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	vec3 lightCol;
};

void main()
{
	fColour = texture(inputTexture, TexCoords);
}