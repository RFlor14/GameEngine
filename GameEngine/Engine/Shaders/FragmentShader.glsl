#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

// Enables the use as a 2D texture image.
uniform sampler2D inputTexture;

uniform light lightConstruct;
uniform vec3 cameraPos;

out vec4 fColour;

// Added light struct (week 7)
struct light
{
	vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	vec3 lightColor;
};

void main()
{
	// ambient
	vec3 ambient = light.ambient * texture(inputTexture, TexCoords).rgb * light.lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.diffuse) * texture(inputTexture, TexCoords).rgb;

	// specular
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * light.specular) * light.lightColor;


	vec3 result = ambient + diffuse + specular;

	fColour = vec4(result, 1.0f);
}