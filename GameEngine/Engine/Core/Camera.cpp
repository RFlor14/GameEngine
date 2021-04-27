#include "Camera.h"

#include "../Core/CoreEngine.h"

// Set up all default value for all variables
std::vector<LightSource*> Camera::lightSources = std::vector<LightSource*>();

Camera::Camera() : position(glm::vec3()), fieldOfView(0.0f), forward(glm::vec3()), up(glm::vec3()),
right(glm::vec3()), worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f), yaw(0.0f), pitch(0.0f),
perspective(glm::mat4()), orthographic(glm::mat4()), view(glm::mat4())
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f); // we want it towards the screen so [-1.0f (on z)]
	up = glm::vec3(0.0f, 1.0f, 0.0f); // camera is upward so [1.0f (on y)]
	worldUp = up;

	// Essentially the world boundary
	nearPlane = 2.0f; // lens of our world
	farPlane = 50.0f; // how far you render

	/*
	 [yaw] how much left or right (from the origin) it's looking at the world.
	 If set to 0, vector will point to the right, [-90] makes it look on the
	 right direction.

	 [pitch] how much it's looking up or down at the world.
	*/
	yaw = -90.0f; 
	pitch = 0.0f; 

	/*
	 [perspective] uses the ratio of the screen, width / height.

	 [orthographic] parameters
	 1) [0.0] left plane
	 2) [ScreenWidth] right plane, screen's maximum x value
	 3) [0.0f] bottom of the screen
	 4) [ScreenHeight] top, screen's maximum y value
	 5) [-1.0f] nearPlane
	 6) [1.0f] farPlane
	*/
	perspective = glm::perspective(fieldOfView,
		CoreEngine::GetInstance()->GetScreenWidth() /
		CoreEngine::GetInstance()->GetScreenHeight(),
		nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(),
		0.0f, CoreEngine::GetInstance()->GetScreenHeight(), -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	if (lightSources.size() > 0)
	{
		for (auto l : lightSources)
		{
			delete l;
			l = nullptr;
		}
		lightSources.clear();
	}
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetView() const
{
	return view;
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::AddLightSources(LightSource* source_)
{
	lightSources.push_back(source_);
}

std::vector<LightSource*> Camera::GetLightSources()
{
	return lightSources;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	/*
	 Depending on the offset of the mouse position,
	 we change the yaw and/or the pitch of the camera.
	*/

	offset_ *= 0.05f; // Mouse sens

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f) 
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	if (yaw < 0.0f)
	{
		yaw += 360.0f;
	}
	if (yaw > 360.0f)
	{
		yaw -= 360.0f;
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseZoom(int y_)
{
	/* 
	 Safety net to make sure scroll happened,
	 and it's not = 0.

	 [2.0f] is zoom speed	
	*/
	if (y_ < 0 || y_ > 0)
	{
		position += static_cast<float>(y_) * (forward * 2.0f);
	}

	UpdateCameraVectors();
} 


void Camera::UpdateCameraVectors()
{
	/*
	 Updates the value of the forward, up, and right vectors.

	 At the end, it also updates for the view matrix. 
	*/
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	forward = glm::normalize(forward);

	/*
	 [Cross product]

	 [right] First do the cross product of the cameras forward
	 vector and the world's up vector.

	 cameras [up] vector, do the cross product of the cams right
	 and fortward, then normalize, and set the variable = result
	 of normalization.
	*/
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));

	/*
	 view matrix is updated here because we use forward and up 
	 vectors of the camera.

	 [position + forward] essentialy locks the camera to just
	 look at its direction no matter how its moved.
	*/
	view = glm::lookAt(position, position + forward, up);
}
