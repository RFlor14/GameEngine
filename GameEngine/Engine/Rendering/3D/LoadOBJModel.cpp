#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), 
normals(std::vector<glm::vec3>()), textureCoords(std::vector<glm::vec2>()),
indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()),
textureIndices(std::vector<unsigned int>()), meshVertices(std::vector<Vertex>()),
subMeshes(std::vector<SubMesh>()), currentTexture(0)
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	/*
	 Order is important

	 First call the load material library (opens mtl file, and
	 read through it)

	 After loading that mat lib file, call the private Load model
	 function.
	*/
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

/*
 Happens when we finished going through all the data of
 a specific mesh.
*/
void LoadOBJModel::PostProcessing()
{
	/*
	 Loop through all of the indices,
	 Create a new vert obj,
	 Set vert pos, norm, texCoord
	*/
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.textureID = currentTexture;

	subMeshes.push_back(mesh);

	// Clear everything out
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentTexture = 0;
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open OBJ file: " + filePath_,
			"LoadOBJModel.cpp", __LINE__);
		return;
	}

	std::string line;
	while (std::getline(in, line))
	{
		//VERTEX DATA
		/*
		 Basically read through the file,
		 if it starts with "v " get the numbers for that.

		 Then create a string stream, with whatever is in the 
		 line from position two and onwards.

		 Then take the first float point data you find, in this
		 case x, then y, then z
		*/
		if (line.substr(0, 2) == "v ")
		{
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}

		//NEW MESH
		/*
		 Before calling post processing, check to make sure that
		 indices has a size greater than 0, meaning we checked
		 face data.

		 If true call post processing,
		 If true/false call load material with whatever comes
		 after "usemtl ".
		*/
		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size())
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}

	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(matName_, "Resources/Textures/" + matName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	}
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	// Uses ifstream to open an mtl file
	std::ifstream in(matFilePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL file: " + matFilePath_, "LoadOBJModel.cpp", __LINE__);
	}

	/*
	 Create a string called line,
	 Use getline function (takes in a file and then a string for the line)
	 then fill the line string w/ what is the current line in the function.
	*/
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			LoadMaterial(line.substr(7));
		}
	}
}
