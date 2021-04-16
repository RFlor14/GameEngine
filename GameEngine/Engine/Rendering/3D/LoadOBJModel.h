#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include <sstream>
#include "Mesh.h"
#include "../../Graphics/TextureHandler.h"

class LoadOBJModel
{
public:
	LoadOBJModel();
	~LoadOBJModel();

	// Takes in path for Obj and mtl.
	void LoadModel(const std::string& objFilePath_,
		const std::string& mtlFilePath_);

	std::vector<SubMesh> GetSubMeshes();

private:

	/*
	 Once we're done looking at single meshes, do post processing work
	 to get all the data from OBJ into the sub meshes object.
	*/
	void PostProcessing();

	// Looks at the obj file and getting all the data out of it.
	void LoadModel(const std::string& filePath_);

	// Goes to texture handler and creating the texture if it's not created.
	void LoadMaterial(const std::string& matName_);

	/*
	 Opens mtl file, get specific mat that needs to load, 
	 then call load material function.
	*/ 
	void LoadMaterialLibrary(const std::string& matFilePath_);

	
	std::vector<glm::vec3> vertices; // Holds 3d vectors
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords; // 2d vectors
	std::vector<unsigned int> indices, normalIndices, textureIndices; // deals w/ face data
	std::vector<Vertex> meshVertices; 
	std::vector<SubMesh> subMeshes;

	GLuint currentTexture;
};

#endif // LOADOBJMODEL_H

