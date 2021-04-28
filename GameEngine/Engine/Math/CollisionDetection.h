#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Core/Camera.h"

struct Ray;
struct BoundingBox;

class CollisionDetection
{
public:
	//singleton
	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator=(const CollisionDetection&) = delete;
	CollisionDetection& operator=(CollisionDetection&&) = delete;

	/*
	 Since its a fully static class, we delete the
	 default constructor, and the copy and move constructors.
	*/
	CollisionDetection() = delete;
	~CollisionDetection();

	static Ray MousePosToWorldRay(glm::vec2 mouseCoords_, float screenWidth_,
		float screenHeight_, Camera* camera_);

	// Intersection function or collision detection function
	static bool RayObbIntersection(Ray* ray_, BoundingBox* box_);


private:
};


#endif // !COLLISIONDETECTION_H




