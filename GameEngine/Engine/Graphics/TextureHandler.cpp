#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;

std::vector<Texture*> TextureHandler::textures = std::vector<Texture*>();

TextureHandler::TextureHandler()
{
	textures.reserve(10);
}

TextureHandler::~TextureHandler()
{
	OnDestroy();
}

TextureHandler* TextureHandler::GetInstance()
{
	/*
	 If texture hasnt been created yet, reset and create a
	 new instance of the texture handler.
	*/
	if (textureInstance.get() == nullptr)
	{
		textureInstance.reset(new TextureHandler);
	}

	return textureInstance.get();
}

void TextureHandler::OnDestroy()
{

	if (textures.size() > 0)
	{

		for (auto t : textures)
		{
			/*
			 Call OpenGL's own delete texture first, and actually
			 deletes it (if it exists);
			*/ 
			glDeleteTextures(sizeof(GLuint), &t->textureID);

			delete t;
			t = nullptr;
		}

		// clears out the vector
		textures.clear();

	}
}

void TextureHandler::CreateTexture(const std::string& textureName_, const std::string& textureFilePath_)
{
	if (GetTextureData(textureName_))
	{
		return;
	}

	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFilePath_.c_str());

	// Debug, check if something went wrong, if so, clean up memory.
	if (surface == nullptr)
	{
		Debug::Error("Surface for texture " + textureName_ + " failed to be created ",
			"TextureHandler.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}

	/*
	 Go through SDL,
	 Generate a [1] texture and give that textures ID,
	 Bind to a 2D texture,

	 [ternary operator] set mode of the texture depending on the bytes per pixel.
	 in a way it's like an if statement, 
	 [int mode = 0, if(byperpi == 4){mode = RGBA}else{mode = RGB}
	*/
	glGenTextures(1, &t->textureID);
	glBindTexture(GL_TEXTURE_2D, t->textureID);
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0,
		mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*
	 [GL_Linear] creates a smoother look, although it could look blurred at times.
	 using a high resolution could help remove the blurriness.

	 [Mipmap] holds a collection of images based on the texture image where each
	 image is half the size of the previous one. Then after a certain distance,
	 OpenGL will start to use a different mipmap that is best suited for the
	 distance to the object.
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	t->width = static_cast<float>(surface->w);
	t->height = static_cast<float>(surface->h);
	t->textureName = textureName_;

	textures.push_back(t);

	SDL_FreeSurface(surface);
	surface = nullptr;
}


/*
 Since vectors are used instead of an unordered map, loop through entire vector,
 since theres no key, this type of check is created.

 How it works:
 Go through each element, 
 check if they have the same name as the string that's passed in as a paraameter.
*/
const GLuint TextureHandler::GetTexture(const std::string& textureName_)
{
	/*
	 Same name?

	 return the [textureID] of the element we're on.
	*/
	for (auto t : textures)
	{
		if (t->textureName == textureName_)
		{
			return t->textureID;
		}
	}

	return 0;
}

const Texture* TextureHandler::GetTextureData(const std::string textureName_)
{
	/*
	 Same name?

	 return the element we're on.
	*/
	for (auto t : textures)
	{
		if (t->textureName == textureName_)
		{
			return t;
		}
	}
	return nullptr;
}


