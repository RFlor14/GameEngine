#include "OctSpatialPartition.h"

int OctNode::childNum = 0;

OctNode::OctNode(glm::vec3 position_, float size_, OctNode* parent_) : 
    octBounds(nullptr), parent(nullptr), children(),
    objectList(std::vector<GameObject*>())
{
    objectList.reserve(10);

    octBounds = new BoundingBox();
    octBounds->minVert = position_;
    octBounds->maxVert = position_ + glm::vec3(size_);

    size = size_;
    parent = parent_;

    /*
     Go through children array,
     for each element in the array make sure
     that it = nullptr.

     We do this because when we create a node,
     we dont know if its going to be a leaf
     or not, so always assume its going
     to start out as a leaf node.

     If need be, it will use the octify
     function to creale all of its children.
    */
    for (int i = 0; i < CHILDREN_NUMBER; i++)
    {
        children[i] = nullptr;
    }
}

OctNode::~OctNode()
{
    // Delete bounding box
    delete octBounds;
    octBounds = nullptr;
    
    // Properly manage the pointers to game object
    if (objectList.size() > 0) 
    {
        for (auto obj : objectList)
        {
            obj = nullptr;
        }
        objectList.clear();
    }

    // Properly deletes array of children
    for (int i = 0; i < CHILDREN_NUMBER; i++)
    {
        /*
         Check if child is not equal to nullptr,
         if not delete it.
        */
        if (children[i] != nullptr)
        {
            delete children[i];
        }

        /*
         If it doesnt exist or not, make
         sure the pointer is set equal
         to nullptr.
        */
        children[i] = nullptr;
    }

}

/*
 Creates all of the children for as many depth as needed
*/
void OctNode::Octify(int depth_)
{
    /*
     Creates all of the children,

     Verify the depth is greater than 0 and that [this] oct node
     has been initialized as a poitner.

     [NOTE] the side of each cube is equal to half the side of the parent,
     so each cube is an eigth of its parent.

     EITHER ADD HALF OR NOT, NO POINT WE'RE SUBTRACTING HALF.

     First) initalize each specific child in the array.
     
     Second)
     position: the position is the minimum vertex of the beginning of the bounding box of the node.
     size: we pass in half var
     Last param: parent we pass [this] because this specific oct node is creating its children.

     Example TLF - Since its top, we add half to Y || front, add half to z || left, do nothing 
     For the opposite sides, just do the opposite of how we did it.
    */
    if (depth_ > 0 && this)
    {
        float half = size / 2.0f;
        children[static_cast<int>(OctChildren::OCT_TLF)] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
        children[static_cast<int>(OctChildren::OCT_BLF)] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z + half), half, this);

        children[static_cast<int>(OctChildren::OCT_BRF)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z + half), half, this);
        children[static_cast<int>(OctChildren::OCT_TRF)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);

        children[static_cast<int>(OctChildren::OCT_TLR)] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z), half, this);
        children[static_cast<int>(OctChildren::OCT_BLR)] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z), half, this);

        children[static_cast<int>(OctChildren::OCT_BRR)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z), half, this);
        children[static_cast<int>(OctChildren::OCT_TRR)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z), half, this);

        childNum += 8;
    }

    /*
     Verifies depth is > 0 and [this] object exists.

     As long as depth > 0, go and create a loop that
     runs for each possible child.

     Then for each child, call octify.

     (depth - 1) ensures that eventually these 
     statements will return flase because
     depth will eventually be 0, and stops
     the reccursion.
    */
    if (depth_ > 0 && this)
    {
        for (int i = 0; i < CHILDREN_NUMBER; i++) 
        {
            children[i]->Octify(depth_ - 1);
        }
    }
}

OctNode* OctNode::GetParent()
{
    return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos_)
{
    return children[static_cast<int>(childPos_)];
}

void OctNode::AddCollisionObject(GameObject* obj_)
{
    objectList.push_back(obj_);
}

int OctNode::GetObjectCount() const
{
    return objectList.size();
}

bool OctNode::IsLeaf() const
{
    if (children[0] == nullptr ) 
    {
        return true;
    }

    return false;
}

BoundingBox* OctNode::GetBoundingBox() const
{
    return octBounds;
}

int OctNode::GetChildCount() const
{
    return childNum;
}

OctSpatialPartition::OctSpatialPartition(float worldSize_) : 
    root(nullptr), rayIntersectionList(std::vector<OctNode*>())
{
    root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr);
    root->Octify(3);
    std::cout << "There are " << root->GetChildCount() << " child nodes" << std::endl;

    rayIntersectionList.reserve(20);

}

OctSpatialPartition::~OctSpatialPartition()
{
    if (rayIntersectionList.size() > 0)
    {
        for (auto cell : rayIntersectionList)
        {
            cell = nullptr;
        }
        rayIntersectionList.clear();
    }

    delete root;
    root = nullptr;
}

void OctSpatialPartition::AddObject(GameObject* obj_)
{
    /*
     Calls in the private recursive function
     and will pass in the root node, because
     the root node is where we want to start on
     and the specific object that we want
     to add to the spatial partitioning system.
    */
    AddObjectToCell(root, obj_);
}

GameObject* OctSpatialPartition::GetCollision(Ray ray_)
{
    /*
     Make sure we clear out the previous collisions
     ray intersection list.
    */
    if (rayIntersectionList.size() > 0)
    {
        for (auto cell : rayIntersectionList)
        {
            cell = nullptr;
        }
        rayIntersectionList.clear();
    }

    /*
     Final part of the preparation phase,
     it will go and fill in this ray
     intersection list vector.
    */
    PrepareCollisionQuery(root, ray_);

    /*
     Collision checking of the get collision funciton.

     Similar to Collision Handler.
    */
    GameObject* result = nullptr;
    float shortestDistance = FLT_MAX;

    /*
     For each node in the array intersection list,
     go through all of the objects in the node's object list,

     for each game object inside the ray intersection list vector,
     check to see if the ray is colliding with the objects
     bounding box.

     If so check the ray intersection distance is less than
     the shortest distance variable.

     If true, set up the result game object pointer = to
     current game object we're looking at, then update the
     shortest distance variable.
    */
    for (auto cell : rayIntersectionList)
    {
        for (auto obj : cell->objectList)
        {
            BoundingBox o = obj->GetBoundingBox();
            if (ray_.IsColliding(&o))
            {
                if (ray_.intersectionDist < shortestDistance)
                {
                    result = obj;
                    shortestDistance = ray_.intersectionDist;
                }
            }
        }

        /*
         If we find an object, stop
         looking for anymore objects,
         then return the game object.
        */
        if (result != nullptr)
        {
            return result;
        }
    }

    /*
     If we checked all of the objects in all of the nodes,
     and there was no result, return nullptr.
    */
    return nullptr;
}

/*
 Check to see if the specific node passed in is a leaf node,
 if it's a leaf node, check to see if the game objects bounding box
 collides with that nodes bounding box.

 If the two bounding boxes collide or [intersect], add
 the game object to the node.

 [if] if node is not a leaf node, create a [for loop] where it
 goes through each child of that node, and recursively calls
 this function on each child.

 Tip: if node is leaf, leaf nodes bound box intersects w/ game obj
 bound box, print out that specific game object that was
 added to the node and its position.
*/
void OctSpatialPartition::AddObjectToCell(OctNode* cell_, GameObject* obj_)
{
    if (obj_->GetBoundingBox().Intersects(cell_->GetBoundingBox()))
    {
        if (cell_->IsLeaf())
        {
            cell_->AddCollisionObject(obj_);
            std::cout << "Added " << obj_->GetTag() << " to cell. Max: " <<
                to_string(obj_->GetBoundingBox().maxVert) << std::endl;
        }

        else
        {
            for (int i = 0; i < CHILDREN_NUMBER; i++)
            {
                AddObjectToCell(cell_->children[i], obj_);
            }
        }
    }
}

/*
 If the node we pass in is a leaf node, check to see if the ray passed
 in intersects with the nodes bounding box.

 If so, add the node to the ray intersection list vector.

 If not, do same thing as AddObjToCell, [for loop] to go through each child
 of the node, and call prepare collision query on the child.

*/
void OctSpatialPartition::PrepareCollisionQuery(OctNode* cell_, Ray ray_)
{
    if (ray_.IsColliding(cell_->GetBoundingBox()))
    {
        if (cell_->IsLeaf())
        {
            rayIntersectionList.push_back(cell_);
        }

        else
        {
            for (int i = 0; i < CHILDREN_NUMBER; i++)
            {
                PrepareCollisionQuery(cell_->children[i], ray_);
            }
        }
    }
}
