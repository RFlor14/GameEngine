#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

// Redeclare the variables
std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector <GameObject*>();
std::vector<GameObject*> CollisionHandler::colliders = std::vector <GameObject*>();

CollisionHandler::CollisionHandler()
{
    colliders.reserve(10);
    prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
    OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()
{
    /*
     Check to see if the instance has been created,
     if not, pass in a new the instance of the
     specific class.
    */
    if (collisionInstance.get() == nullptr)
    {
        collisionInstance.reset(new CollisionHandler);
    }

    /*
     Even if its created or not, return the value
     of the get function that we call on the
     unique ptr.
    */
    return collisionInstance.get();
}

void CollisionHandler::OnCreate()
{
    colliders.clear();
    prevCollisions.clear();
}

void CollisionHandler::AddObject(GameObject* go_)
{
    colliders.push_back(go_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
    Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_,
        CoreEngine::GetInstance()->GetScreenWidth(),
        CoreEngine::GetInstance()->GetScreenHeight(),
        CoreEngine::GetInstance()->GetCamera());

    /*
     Check to see if a collision has occured with the ray and
     all of the collideable game objects that are in the scene.

     Need two variables
     1) game object that represents the hit object
     2) need this variable because if we have two objects in 
     the scene, make sure that the closest object to the
     camera was hit.
    */
    GameObject* hitResult = nullptr;
    float shortestDistance = FLT_MAX;

    /*
     Check to see which bounding box the ray
     from the mouse hit.

     Loop through all potentially collideable objects.

     Check to see if the ray is even colliding w/ the
     bounding box.

     If a collision occured, make sure that it is 
     the object that is the nearest to the camera.
    */
    for (auto g : colliders)
    {
        if (mouseRay.IsColliding(&g->GetBoundingBox()))
        {
            /*
             Then compare the intersection distance of
             the mouse ray.

             If intersection distance is less than the
             shortest distance variable that we created,

             set the hit result game object to the current
             game object that we're looking at in
             the colliders vector.

             Then update the shortest distance variable
             to now equal the rays intersection distance.
            */
            if (mouseRay.intersectionDist < shortestDistance)
            {
                hitResult = g;
                shortestDistance = mouseRay.intersectionDist;
            }
        }
    }

    // Check to see if a hit result occured
    if (hitResult)
    {
        hitResult->SetHit(true, buttonType_);
    }

    /*
     If a hit occured, make sure that anything
     that was previously hit is now not hit 
     anymore.
    */
    for (auto c : prevCollisions)
    {
        if (hitResult != c && c != nullptr)
        {
            c->SetHit(false, buttonType_);
        }
    }

    // Clear out prevCollisions vector
    prevCollisions.clear();

    /*
     Then add the newly hit object to that previous
     collisions vector.
    */
    if (hitResult)
    {
        prevCollisions.push_back(hitResult);
    }
}

void CollisionHandler::OnDestroy()
{
    /*
     Makes sure that the two vectors are cleared out.
     
     for each loop, we go through each element in the vector.

     We're not deleting th epointer in these two because we're 
     in the collision handler class. 
     
     (it doesnt have the responsibility of deleting game 
     object pointers, it's the scene graph's.)
    */

    for (auto entry : colliders)
    {
        entry = nullptr;
    }
    colliders.clear();

    for (auto entry : prevCollisions)
    {
        entry = nullptr;
    }
    prevCollisions.clear();
    
}


