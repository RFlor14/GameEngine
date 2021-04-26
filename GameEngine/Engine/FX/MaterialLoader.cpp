#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	/*
	 First open up the file,
	 If we cant open it, if statement gets caught and
	 outputs an error.
	*/
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL file: " + filePath_,
			"MaterialLoader.cpp", __LINE__);
		return;
	}

	/*
	 Second, if it's able to open the file.

	 Create a new material object. (the object is a stack variable not a pointer)

	 Then create an empty string for the material's name.
	*/
	Material m = Material();
	std::string matName = "";
	std::string line;

	/*
	 Create a string to hold the current line of the file,
	 then create a while loop using the getline function.
	*/
	while (std::getline(in, line))
	{
		/*
		 If line from pos 0 to 7 equals new empty space,
		 we're looking at the current line of the file (ex Apple_body).

		 If true, check to see if the diffuse map does not equal zero.
		*/
		if (line.substr(0, 7) == "newmtl ")
		{
			if (m.diffuseMap != 0)
			{
				/*
				 Only post processing we're doing is go into the
				 material handler, and add a new material (m).
				*/
				MaterialHandler::GetInstance()->AddMaterial(m);

				/*
				 This basically just clears out all the data that's
				 in the material object.
				*/
				m = Material();
			}

			/*
			 After the if statement, set the materials name to 
			 be what comes after this newmtl line.
			*/
			matName = line.substr(7);
			
			//texture that we're going to use to texture our object.
			m.diffuseMap = LoadTexture(matName);

			// set name of material to be this material name string.
			m.name = matName;
		}
	}

	/*
	 Makes sure that we're adding the very last material to
	 the material handler.
	*/
	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}

	in.close();

}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	/*
	 Similar to LoadOBJ

	 Creating the current texture as a local variable of this function.

	 Get texture by the name we get pased in, if it doesnt work [currentTexture == 0],
	 then create the texture and assign the current texture variable again.
	*/
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0)
	{ 
		TextureHandler::GetInstance()->CreateTexture(fileName_,
			"./Resources/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	
	// If we went into the if statement or not, always return currentTexture.
	return currentTexture;
		
}
