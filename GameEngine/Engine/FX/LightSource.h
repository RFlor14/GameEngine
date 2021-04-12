#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource
{
public:

	LightSource(glm::vec3 lightPos_ = glm::vec3(),
		float ambient_ = 0.0f,
		float diffuse_ = 0.0f,
		float specular_ = 0.0f,
		glm::vec3 lightColor_ = glm::vec3(0.0f, 1.0f, 0.0f));

	~LightSource();

	glm::vec3 GetLightPos() const;
	float GetAmbient() const;
	float GetDiffuse() const;
	float GetSpecular() const;
	glm::vec3 GetLightColor() const;


	void SetLightPos(glm::vec3 lightPos_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);
	void SetSpecular(float specular_);
	void SetLightColor(glm::vec3 lightColor_);

private:
	glm::vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	glm::vec3 lightColor;
};


#endif LIGHTSOURCE_H


