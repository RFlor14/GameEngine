#ifndef RAY_H
#define RAY_H

#include "BoundingBox.h"
#include "CollisionDetection.h"

struct Ray 
{
	glm::vec3 origin;
	glm::vec3 direction;

	/*
	 Help us calculate the collision
	 detection and what specific object
	 was hit.
	*/
	float intersectionDist;

	// Default constructor
	inline Ray()
	{
		origin = glm::vec3();
		direction = glm::vec3();
		intersectionDist = 0.0f;
	}

	inline Ray(glm::vec3 origin_, glm::vec3 direction_)
	{
		origin = origin_;
		direction = direction_;
		intersectionDist = 0.0f;
	}

	/*
	 Operator overload, way to define special things
	 that you want to do for operator.

	 In this case we're creating an operator overload
	 for this equal sign. 1 = means its an assignment
	 operator.
	*/
	inline Ray& operator =(const Ray& ray_)
	{
		origin = ray_.origin;
		direction = ray_.direction;
		intersectionDist = 0.0f;
	}

	/*
	 Used to really check collision detection with
	 a ray and bounding box.
	*/
	inline bool IsColliding(BoundingBox* box_)
	{
		intersectionDist = -1.0f;
		return CollisionDetection::RayObbIntersection(this, box_);
	}

};

#endif // !RAY_H

 