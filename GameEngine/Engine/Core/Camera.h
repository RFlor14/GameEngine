#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp> // Enables acess to all of the glm data types.
#include <glm/gtc/matrix_transform.hpp> // Enables acess to special matrix functions.
#include <vector>
#include "../FX/LightSource.h"


class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	/*
	 Reminder:
	 const at the end lets us know that there will be no change in the actual function.
	*/
	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;

	void AddLightSources(LightSource* source_);
	std::vector<LightSource*> GetLightSources();

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

private:

	void UpdateCameraVectors(); // Updates all of the camera vectors
	glm::vec3 position; // cameras world position
	glm::mat4 perspective, orthographic, view; // cameras important matrices (we're doing 3D = perspective)
	float fieldOfView; // change of the screen zoom

	//How we define rotation in 3D
	float yaw, pitch; 

	/*
	 Anything infront of near plane wont be rendered anything behind 
	 the far plane is also not going to be rendered.
	*/ 
	float nearPlane, farPlane; 

	/*
	 [up vector] is the cameras upward direction
	 [wolrdUp vector] is a reference to what is the [up] direction of the world.
	*/
	glm::vec3 forward, up, right, worldUp; 

	// LightSource pointers
	static std::vector<LightSource*> lightSources;

};



#endif // !CAMERA_H
