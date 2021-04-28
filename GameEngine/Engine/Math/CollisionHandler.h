#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Ray.h"
#include "../Rendering/3D/GameObject.h"

class CollisionHandler
{
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();

	void OnCreate();

	
	/*
	 Gets passed in a collideable object,

	 Will add this collideable object to the
	 collection of collideable objects that the
	 collision handler holds.
	*/
	void AddObject(GameObject* go_);

	/*
	 Called whenever we want to do something in
	 terms of collision handling or collision checking.
	*/
	void MouseUpdate(glm::vec2 mousePosition_, int buttonType_);
	void OnDestroy();

private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionInstance;
	friend std::default_delete<CollisionHandler>;

	// Potential collideable objects that are in the scene
	static std::vector<GameObject*> colliders;

	// Holds all of the previously collided objects w/ game objects.
	static std::vector<GameObject*> prevCollisions;
};

#endif // !COLLISIONHANDLER_H

