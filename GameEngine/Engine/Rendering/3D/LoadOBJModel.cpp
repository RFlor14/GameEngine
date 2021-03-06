#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), 
normals(std::vector<glm::vec3>()), textureCoords(std::vector<glm::vec2>()),
indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()),
textureIndices(std::vector<unsigned int>()), meshVertices(std::vector<Vertex>()),
subMeshes(std::vector<SubMesh>()), currentMaterial(Material())
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

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox;
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
		vert.position = vertices[indices[i] - 1];
		vert.normal = normals[normalIndices[i] - 1];
		vert.textureCoordinates = textureCoords[textureIndices[i] - 1];
		meshVertices.push_back(vert);
	}

	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	// Clear everything out
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	/*
	 This makes sure that we're clearing out all
	 of the data that's inside of current material.
	 
	 So when it comes to the next mesh that we're 
	 loading, we wont have nay data in that
	 current material.
	*/
	currentMaterial = Material();
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
	boundingBox.maxVert = glm::vec3(-1000.0f);
	boundingBox.minVert = glm::vec3(1000.0f);

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

			/*
			 Basically just binding the x,y,z to the bounding box,
			 depending on if the current value is < or > the 
			 bounding box's min and max.
			*/
			if (boundingBox.minVert.x > x) boundingBox.minVert.x = x;
			if (boundingBox.minVert.y > y) boundingBox.minVert.y = y;
			if (boundingBox.minVert.z > z) boundingBox.minVert.z = z;

			if (boundingBox.maxVert.x < x) boundingBox.maxVert.x = x;
			if (boundingBox.maxVert.y < y) boundingBox.maxVert.y = y;
			if (boundingBox.maxVert.z < z) boundingBox.maxVert.z = z;

			vertices.push_back(glm::vec3(x, y, z));

		}

		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream vn(line.substr(3));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		//TEXTURE COORDS
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(3));
			float x, y;
			vt >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//FACE DATA
		else if (line.substr(0, 2) == "f ")
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			char slash;
			std::stringstream v(line.substr(2));
			v >> vertexIndex[0] >> slash >> uvIndex[0] >> slash >> normalIndex[0] >>
				vertexIndex[1] >> slash >> uvIndex[1] >> slash >> normalIndex[1] >>
				vertexIndex[2] >> slash >> uvIndex[2] >> slash >> normalIndex[2];

			indices.push_back(vertexIndex[0]);
			indices.push_back(vertexIndex[1]);
			indices.push_back(vertexIndex[2]);

			textureIndices.push_back(uvIndex[0]);
			textureIndices.push_back(uvIndex[1]);
			textureIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
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
			if (indices.size() > 0)
			{ 
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}

	PostProcessing();
	in.close();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}
