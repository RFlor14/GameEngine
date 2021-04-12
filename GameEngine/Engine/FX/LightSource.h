#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource
{
public:

	LightSource(glm::vec3 lightPos_,
		float ambient_,
		float diffuse_,
		float specular_,
		glm::vec3 lightColour_);

	~LightSource();

	glm::vec3 GetLightPos() const;
	float GetAmbient() const;
	float GetDiffuse() const;
	float GetSpecular() const;
	glm::vec3 GetLightColour() const;


	void SetLightPos(glm::vec3 lightPos_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);
	void SetSpecular(float specular_);
	void SetLightColour(glm::vec3 lightColour_);

private:
	glm::vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	glm::vec3 lightColour;
};


#endif LIGHTSOURCE_H


