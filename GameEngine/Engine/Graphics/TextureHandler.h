#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <memory>
#include <string>
#include <vector>
#include <SDL.h>
#include "../Core/Debug.h"
#include <glew.h>


/*
 Get information about texture that is needed to get track of.
*/
struct Texture 
{
	GLuint textureID = 0;
	float width = 0.0f;
	float height = 0.0f;
	std::string textureName = "";

};

class TextureHandler
{
public:
	
	// Singleton to disable copy and move constructors
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator = (const TextureHandler&) = delete;
	TextureHandler& operator = (TextureHandler&&) = delete;

	static TextureHandler* GetInstance();
	void OnDestroy();

	/*
	 [textureName_]  = saving to the texture structure
	 [textureFilePath_] = used to load texture
	*/
	void CreateTexture(const std::string& textureName_,
		const std::string& textureFilePath_);

	/*
	 [GetTexture] = returns the ID of the texture
	 [GetTexture Data] = returns a reference to the entire texture obj
	*/
	const GLuint GetTexture(const std::string& textureName_);
	const Texture* GetTextureData(const std::string textureName_);

private:

	TextureHandler();
	~TextureHandler();

	
	// Singleton is used, so there's a [unique_ptr] & [default_delete]
	static std::unique_ptr<TextureHandler> textureInstance;
	friend std::default_delete<TextureHandler>;


	static std::vector<Texture*> textures;

};
#endif // !TEXTUREHANDLER_H

