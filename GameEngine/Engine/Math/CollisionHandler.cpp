#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

// Redeclare the variables
std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector <GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler()
{
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

void CollisionHandler::OnCreate(float worldSize_)
{
    prevCollisions.clear();
    scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* go_)
{
    if (scenePartition != nullptr)
    {
        scenePartition->AddObject(go_);
    }
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
    Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_,
        CoreEngine::GetInstance()->GetScreenWidth(),
        CoreEngine::GetInstance()->GetScreenHeight(),
        CoreEngine::GetInstance()->GetCamera());

    if (scenePartition != nullptr)
    {
        GameObject* hitResult = scenePartition->GetCollision(mouseRay);

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
            c = nullptr;
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
}

void CollisionHandler::OnDestroy()
{
    delete scenePartition;
    scenePartition = nullptr;

    /*
     Makes sure that the two vectors are cleared out.
     
     for each loop, we go through each element in the vector.

     We're not deleting th epointer in these two because we're 
     in the collision handler class. 
     
     (it doesnt have the responsibility of deleting game 
     object pointers, it's the scene graph's.)
    */

    for (auto entry : prevCollisions)
    {
        entry = nullptr;
    }
    prevCollisions.clear();
    
}


