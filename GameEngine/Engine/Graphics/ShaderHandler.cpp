#include "ShaderHandler.h"

/*
Whenever we have a static var, always redeclare it.
(Like in CoreEngine.h)

When redeclaring it always have the same structure.
*/
std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;

// Set up the [unordered_map]'s default value to be empty.
std::unordered_map<std::string, GLuint> ShaderHandler::programs =
	std::unordered_map<std::string, GLuint>();

ShaderHandler::ShaderHandler(){}

ShaderHandler::~ShaderHandler()
{
	OnDestroy();
}


ShaderHandler* ShaderHandler::GetInstance()
{
	/*
	Most singletons have the same patterns, this can be seen in [CoreEngine GetInstance]

	This if statement check to see if an instance has been created,
	if not reset the the [unique_ptr], other than that
	always return the [unique_ptr].
	*/
	if (shaderInstance.get() == nullptr)
	{
		shaderInstance.reset(new ShaderHandler);
	}
	return shaderInstance.get();
}

void ShaderHandler::CreateProgram(const std::string& shaderName_,
	const std::string& vertexShaderFileName_,
	const std::string& fragmentShaderFilename_)
{
	// Read two files
	std::string vertexShaderCode = ReadShader(vertexShaderFileName_);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFilename_);

	// check any of those are empty
	if (vertexShaderCode == "" || fragmentShaderCode == "")
	{
		return;
	}

	// create fragment/vertex shader
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);
	
	// if both are broken, stop the code
	if (vertexShader == 0 || fragmentShader == 0)
	{
		return;
	}

	GLint linkResult = 0; // create link result
	GLuint program = glCreateProgram(); // actually create the program

	// Attach both vertex and fragment shader
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// link up the program (compile the shader object)
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (!linkResult)
	{
		GLint infoLogLength = 0; // pass in adress of integer
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength); // fill the value of integer
		std::vector<char> programLog(infoLogLength); // create vector w/ size of log length
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]); // pass info into that vector

		// convert vector of characters into string
		std::string programString(programLog.begin(), programLog.end());

		// Debug, and print out error
		Debug::Error("Failed to link " + shaderName_ + ". Error: \n" +
			programString, "ShaderHandler.cpp", __LINE__);

		// since something went wrong, properly delete and clean memory
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(program);

		return;
	}

	// Create a new entry where key is this shader name var, and value is program var.
	programs[shaderName_] = program;


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint ShaderHandler::GetShader(const std::string& shaderName_)
{
	/*
	Pass in the name of the shader you want to get,
	Look through map and check if it exists,
	if it exists, return the value associated w/ the shader name,
	if not, return 0.

	-------
	It iterates through each one of the elements of the unordered map,
	check to see if the key matches what the parameter is. If not,
	go to the next iterator.

	-------
	It ends once it reaches the key that matches the param and
	return what's stored on the key

	or

	if it doesnt find that key return [.end].
	*/
	if (programs.find(shaderName_) != programs.end())
	{
		return programs[shaderName_];
	}
	return 0;
}

void ShaderHandler::OnDestroy()
{
	/*
	(similar to VAO and VBO).

	In this case, it goes through each one of our programs in
	the unordered map.

	For each one, delete the second, because the program has
	(key = string, value = GLuint).
	[.second] gets the value,
	[.first] gets the key.

	After deleting all of the programs, clear out the unordered map.
	*/
	if (programs.size() > 0)
	{
		for (auto p : programs)
		{
			glDeleteProgram(p.second);
		}
		programs.clear();
	}
}

/*
Simple explanation, pass the path of what you want to read,
then output the string that file contains.
*/ 
std::string ShaderHandler::ReadShader(const std::string& filePath_)
{
	// Create a string to represent the content fo the file.
	std::string shaderCode = "";

	// Object used to read the file.
	std::ifstream file;

	/*
	Turn on the flag to check if there's a badbit
	(something wrong w/ the file).

	[try] lets the user run this piece of code.
	1) open file based on file path
	2) create a stringstream (stream class that specifically works on strings)
	3) take file info and pass it to stringstream
	4) close file (we got the data out of the file)
	5) set string = to string inside of the string stream.

	then [catch] this specific type of exception (error)
	and output the debug, if something's wrong return empty string.
	
	All clear, return [shaderCode].
	*/
	file.exceptions(std::ifstream::badbit);
	try 
	{
		file.open(filePath_);
		std::stringstream tmpStream;
		tmpStream << file.rdbuf();
		file.close();
		shaderCode = tmpStream.str();
	}
	catch (std::ifstream::failure error_)
	{
		Debug::Error("Could not read the shader: " + filePath_,
			"ShaderHandler.cpp", __LINE__);
		return "";
	}

	return shaderCode;
}

// Creates shader object
GLuint ShaderHandler::CreateShader(GLenum shaderType_, const std::string& source_, 
	const std::string& shaderName_)
{
	
	// Similar to window class, we set return type of gluint function to glenum var.
	GLint compileResult = 0;
	
	// Create shader based on [shaderType_]
	GLuint shader = glCreateShader(shaderType_);
	
	// Convert string into char* object
	const char* shaderCodePtr = source_.c_str();

	// Get size of the shader
	const int shaderCodeSize = source_.size();

	// Once created, pass in the source of the shader
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);

	/*
	Error check for compile shader line.

	[glGetShaderiv] gets compile status of shader and set
	the value to the status of the shader compile.

	if [compileResult] = 0, start going through and print out
	where and what went wrong.
	*/
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (!compileResult)
	{
		GLint infoLogLength = 0; // pass in adress of integer
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength); // fill the value of integer
		std::vector<char> shaderLog(infoLogLength); // create vector w/ size of log length
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]); // pass info into that vector

		// convert vector of characters into string
		std::string shaderString(shaderLog.begin(), shaderLog.end()); 
		
		// Debug, and print out error
		Debug::Error("Error compiling shader " + shaderName_ + ". Error: \n" +
			shaderString, "ShaderHandler.cpp", __LINE__);

		return 0; // since it's a GLuint
	}
	
	//return the index of the shader object created
	return shader;
}

