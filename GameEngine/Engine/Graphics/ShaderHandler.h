#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <sstream> // gives acess to string and if stream.
#include <unordered_map>
#include <vector>
#include <memory> // makes it a singleton
#include <glew.h>
#include "../Core/Debug.h"

/*
Folder: Handles anything that does with graphics.
*/

class ShaderHandler
{
public:

	/*
	Disables the creation of copy or move constructors. Ensures that no two objects are the same.

	This can be used for any class that you want, where you want to make sure
	no one can be able to use a copy or move constructor for it.

	Makes sure that if anyone tries to move or a copy constructor of this class, give out an error.
	*/
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator = (const ShaderHandler&) = delete;
	ShaderHandler& operator = (ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();

	/*
	To create a program we're passing in the name of the program,
	then the path to the vertex shader file,
	and the path to the fragment shader file.

	With those inputs it will call other functions and create 
	the openGL program.
	*/
	void CreateProgram(const std::string& shaderName_,
		const std::string& vertexShaderFileName_,
		const std::string& fragmentShaderFilename_);

	/*
	Pass in the name of the shader you want to get and returns 
	the specific shader.
	*/
	GLuint GetShader(const std::string& shaderName_);

	void OnDestroy();

private:

	// Private since we're creating a singleton
	ShaderHandler();
	~ShaderHandler();

	// All of these are private since no other classes need to use them.
	static std::unique_ptr<ShaderHandler> shaderInstance;
	friend std::default_delete<ShaderHandler>;

	/*
	[ReadShader] reads a shader file, pass in the file of the shader you want,
	return a string of what's in that file.

	[CreateShader] in simple terms, it just creates a shader object.
	Pass in what type of shader (vertex/fragment),
	pass in string for the source (source code of vertex/fragment shader from [ReadShader]),
	passes in string of the shader name for debugging.
	*/
	std::string ReadShader(const std::string& filePath_);
	GLuint CreateShader(GLenum shaderType_, const std::string& source_,
		const std::string& shaderName_);

	/*
	Singleton,

	It keep track of all the shader programs that we have created.

	A map is you have a key/value pair entry into the map.
	Like a dictionary you have a word then a definition.
	Word = Key, Definition = Value.

	In this case, key as a string, and value as Gluint. The key is what we 
	look for in the map, then we get a specific value with that key.

	[unordered] puts the entries in whatever order, making insertion and
	searching much quicker.
	*/
	static std::unordered_map<std::string, GLuint> programs;
		
};

#endif // !SHADERHANDLER_H


