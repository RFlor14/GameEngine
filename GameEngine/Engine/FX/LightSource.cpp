#include "LightSource.h"

LightSource::LightSource(glm::vec3 lightPos_, float ambient_, float diffuse_, float specular_, glm::vec3 lightColour_) : lightPos(lightPos_), ambient(ambient_), diffuse(diffuse_), specular(specular_), lightColour(lightColour_)
{

}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetLightPos() const
{
	return lightPos;
}

float LightSource::GetAmbient() const
{
	return ambient;
}

float LightSource::GetDiffuse() const
{
	return diffuse;
}

float LightSource::GetSpecular() const
{
	return specular;
}

glm::vec3 LightSource::GetLightColour() const
{
	return lightColour;
}

void LightSource::SetLightPos(glm::vec3 lightPos_)
{
	lightPos = lightPos_;
}

void LightSource::SetAmbient(float ambient_)
{
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_)
{
	diffuse = diffuse_;
}

void LightSource::SetSpecular(float specular_)
{
	specular = specular_;
}

void LightSource::SetLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
}
