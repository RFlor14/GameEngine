#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"


CollisionDetection::~CollisionDetection()
{
}

/*
 Converts mouse coordinate (the 2D vector is on the near plane) to
 a ray that goes through our scene (ray that's int the WorldSpace).
*/
Ray CollisionDetection::MousePosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_)
{
	// NDC is normalized device coordinates
	
	/*
	 1. We need to find the start and end point of the ray
	 Since we're using mouse coordinates, the start and end
	 is in the NDC space. 

	 Then convert NDC to worldspace.
	*/
	glm::vec4 rayStartNDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f,
		(mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f,
		-1.0f, 1.0f);
	
	glm::vec4 rayEndNDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f,
		(mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f,
		0.0f, 1.0f);

	/*
	 If we want to go back to world space, we need to go backwards,
	 in this case, we use inverse.	 

	 Get the inverse of the perspective matrix multiplied by the view
	 then taking in the inverse of that multiplication will essentially
	 undo the spaces that the perspective and view matrices get you to.
	*/
	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	glm::vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	glm::vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);
	
	return Ray(glm::vec3(rayStartWorld), rayDirWorld);

}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_)
{
	return false;
}

