#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include "../Graphics/MaterialHandler.h"
#include "../Graphics/TextureHandler.h"
#include <sstream>

class MaterialLoader
{
public:

	MaterialLoader(const MaterialLoader&) = delete;
	MaterialLoader(MaterialLoader&&) = delete;
	MaterialLoader& operator=(const MaterialLoader&) = delete;
	MaterialLoader& operator=(MaterialLoader&&) = delete;

	MaterialLoader() = delete;
	~MaterialLoader();

	/*
	 Function to load the material

	 Takes in a path for the MTL file,
	 opens that file and loads all of the data.
	*/
	static void LoadMaterial(std::string filePath_);

private:

	/*
	 Function to load in the texture

	 Takes in the name of the texture and loads it that way.
	*/
	static GLuint LoadTexture(std::string fileName_);

};


#endif // !MATERIALLOADER_H


