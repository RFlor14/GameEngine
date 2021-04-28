#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

// Struxt by default is public
struct BoundingBox
{
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;

	inline BoundingBox()
	{
		maxVert = minVert = glm::vec3();
		transform = glm::mat4();
	}

	/*
	 Takes in min, max vertex, and transformation matrix.

	 Then, set up the class variable values, and set it
	 to equal what gets passed in as parameters.
	*/
	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_)
	{
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_)
	{
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		glm::vec3 otherMinCorner = GetTransformedPoint(box_->minVert, box_->transform);
		glm::vec3 otherMaxCorner = GetTransformedPoint(box_->maxVert, box_->transform);

		if (minCorner.x <= otherMaxCorner.x && maxCorner.x >= otherMinCorner.x && 
			minCorner.y <= otherMaxCorner.y && maxCorner.y >= otherMinCorner.y && 
			minCorner.z <= otherMaxCorner.z && maxCorner.z >= otherMinCorner.z)
		{
			return true;
		}
	
		return false;

	}

private:

	/*
	 Need a second gettransformed point function because during the box box
	 intersection, doing it using the AABB is much simpler.	

	 Take bounding box, and convert it to an axis alligned bounding box.

	 To do this, move the min and max points of the bounding box, and
	 translate them with the translation in the transformation matrix
	 that the bounding box has in it.
	*/
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_)
	{ 
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};

#endif // !BOUNDINGBOX_H
