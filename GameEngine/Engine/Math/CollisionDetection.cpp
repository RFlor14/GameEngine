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
Ray CollisionDetection::MousePosToWorldRay(glm::vec2 mouseCoords_, float screenWidth_,
	float screenHeight_, Camera* camera_)
{
	// NDC is normalized device coordinates
	
	/*
	 1. We need to find the start and end point of the ray
	 Since we're using mouse coordinates, the start and end
	 is in the NDC space. 

	 Then convert NDC to worldspace.
	*/
	glm::vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f,
		(mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
		-1.0f, 1.0f);
	
	glm::vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f,
		(mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
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
	/*
	 Set up variables for convenience.
	*/
	glm::mat4 modelMatrix = box_->transform;
	glm::vec3 rayOrigin = ray_->origin;
	glm::vec3 rayDirection = ray_->direction;
	glm::vec3 boxMin = box_->minVert;
	glm::vec3 boxMax = box_->maxVert;

	float tMin = CoreEngine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetFarPlane();

	/*
	 To get the world position (very last column of the model matrix
	 from the box) we use [], just like for a vector or an array.

	 When we're looking at the fourth column, we need to use
	 the number 3 for the index value.

	 Since worldPos is a 3d vector we're using x,y,z of the
	 model matrix last column.
	*/
	glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	
	// Checks the difference of.
	glm::vec3 delta = worldPos - rayOrigin;

	// X Axis
	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDeltaX = glm::dot(delta, xAxis);
	float dotDirX = glm::dot(rayDirection, xAxis);
	if (fabs(dotDirX) > 0.001f)
	{
		float t1 = (dotDeltaX + boxMin.x) / dotDirX;
		float t2 = (dotDeltaX + boxMax.x) / dotDirX;

		if (t1 > t2)
		{
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax)
		{
			tMax = t2;
		}

		if (t1 > tMin)
		{
			tMin = t1;
		}

		if (tMax < tMin)
		{
			return false;
		}
	}
	else 
	{
		if (-dotDeltaX + boxMin.x > 0.0f || -dotDeltaX + boxMax.x < 0.0f)
		{
			return false;
		}
	}

	// Y Axis
	glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
	float dotDeltaY = glm::dot(delta , yAxis);
	float dotDirY = glm::dot(rayDirection, yAxis);
	if (fabs(dotDirY) > 0.001f)
	{
		float t1 = (dotDeltaY + boxMin.y) / dotDirY;
		float t2 = (dotDeltaY + boxMax.y) / dotDirY;

		if (t1 > t2)
		{
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax)
		{
			tMax = t2;
		}

		if (t1 > tMin)
		{
			tMin = t1;
		}

		if (tMax < tMin)
		{
			return false;
		}

	}
	else
	{
		if (-dotDeltaY + boxMin.y > 0.0f || -dotDeltaY + boxMax.y < 0.0f)
		{
			return false;
		}
	}


	// Z Axis
	glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	float dotDeltaZ = glm::dot(delta, zAxis);
	float dotDirZ = glm::dot(rayDirection, zAxis);
	if (fabs(dotDirZ) > 0.001f)
	{
		float t1 = (dotDeltaZ + boxMin.z) / dotDirZ;
		float t2 = (dotDeltaZ + boxMax.z) / dotDirZ;

		if (t1 > t2)
		{
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax)
		{
			tMax = t2;
		}

		if (t1 > tMin)
		{
			tMin = t1;
		}

		if (tMax < tMin)
		{
			return false;
		}

	}
	else
	{
		if (-dotDeltaZ + boxMin.z > 0.0f || -dotDeltaZ + boxMax.z < 0.0f)
		{
			return false;
		}
	}

	ray_->intersectionDist = tMin;
	return true;
}

