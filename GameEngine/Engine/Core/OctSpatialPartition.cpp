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
