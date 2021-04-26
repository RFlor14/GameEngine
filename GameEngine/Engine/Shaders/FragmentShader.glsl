#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

// Added light struct (week 7)
struct Light
{
	vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	vec3 lightColour;
};

// Added material struct (week 10)
struct Material
{
	sampler2D diffuseMap;
	float shininess;
	float transparency;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;
uniform vec3 cameraPos;
uniform Material material;

out vec4 fColour;

void main()
{
	// ambient
	vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	// specular
	vec3 viewDir = normalize(cameraPos - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColour;

	vec3 result = ambient + diffuse + specular;

	fColour = vec4(result, material.transparency);
}