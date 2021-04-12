#include "LightSource.h"

LightSource::LightSource(glm::vec3 lightPos_, float ambient_, float diffuse_, float specular_, glm::vec3 lightColor_) :
	lightPos(glm::vec3()), ambient(0), diffuse(0), specular(0), lightColor(glm::vec3(0.0f, 1.0f, 0.0f))
{
	lightPos = lightPos_;
	ambient = ambient_;
	diffuse = diffuse_;
	specular = specular_;
	lightColor = lightColor_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetLightPos() const
{
	return glm::vec3();
}

float LightSource::GetAmbient() const
{
	return 0.0f;
}

float LightSource::GetDiffuse() const
{
	return 0.0f;
}

float LightSource::GetSpecular() const
{
	return 0.0f;
}

glm::vec3 LightSource::GetLightColor() const
{
	return glm::vec3();
}

void LightSource::SetLightPos(glm::vec3 lightPos_)
{
}

void LightSource::SetAmbient(float ambient_)
{
}

void LightSource::SetDiffuse(float diffuse_)
{
}

void LightSource::SetSpecular(float specular_)
{
}

void LightSource::SetLightColor(glm::vec3 lightColor_)
{
}
