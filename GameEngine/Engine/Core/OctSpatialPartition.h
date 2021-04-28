#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

/*
 Helps avoid magic numbers.

 Since we know that we're doing it
 in spatial partiioning in 3D world,
 we're going to be using the oct version,
 which means that we're just going to use 8.
*/
constexpr auto CHILDREN_NUMBER = 8;

/*
 T = Top, B = Bottom
 L = Left, R = Right
 F = Front, R = Rear
*/
enum class OctChildren
{
	OCT_TLF,
	OCT_BLF,
	OCT_BRF,
	OCT_TRF,
	OCT_TLR,
	OCT_BLR,
	OCT_BRR,
	OCT_TRR
};

class OctNode
{
public:
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void Octify(int depth_); // creates all of the children, depth = how many round creations.
	OctNode* GetParent(); // Gets parent
	OctNode* GetChild(OctChildren childPos_); // Gets a specific child

	/*
	 Any sort of collideable object we have in the scene,
	 we add it to its corresponding node. We then need
	 to know what specific object is being added. 

	 Then when we look at the private section of this class,
	 it will be added to the list of game objects. 
	*/
	void AddCollisionObject(GameObject* obj_); 

	/*
	 Returns the number of objects that is inside
	 of this node.
	*/
	int GetObjectCount() const;
	
	// Leaf = no children
	bool IsLeaf() const;

	// Each node has a bounding box 
	BoundingBox* GetBoundingBox() const;

	/*
	 Returns the child count, to make sure
	 we created everything properly so we
	 can get the total number of the children
	 that are created fro the scene in
	 this whole oct tree.
	*/
	int GetChildCount() const;

private:
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	std::vector<GameObject*> objectList;
	float size;
	static int childNum;

};

#endif // !OCTSPATIALPARTITION_H




