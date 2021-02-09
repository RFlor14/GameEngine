#ifndef DEBUG_H
#define	DEBUG_H

#include <iostream>
#include <string>
#include <fstream>


class Debug
{
public:


	/*
	Creates an enum type of specific messages to log for the debugger.

	Enum: essentially creating a variable, each variable has a meaningful name.
	Unsigned short: makes sure that the enum var is equal to the same size as an unsigned short (2 bytes).

	Enum's default value starts at 0, it increases the value by 1 for every type.

	Like any other class' make sure there's a [;] at the end of the brackets.
	*/
	enum class MessageType : unsigned short
	{
		TYPE_NONE = 0, 
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};


	/*
	Disables the creation of copy or move constructors. Ensures that no two objects are the same.

	This can be used for any class that you want, where you want to make sure
	no one can be able to use a copy or move constructor for it.

	Makes sure that if anyone tries to move or a copy constructor of this class, give out an error.
	*/
	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	/*
	1) Note: for OnCreate we're giving it a default value, it's optional to 
	fill in the name, if nothing is filled in, by default the default 
	name would be the [name_] param.

	2) As a setter, it needs to have a specific type parameter.

	3-7) All does the same thing, it logs a specific debug line.

	Each seperate functions is for each type of debug message we can have.

	Reason why they're seperate is that switch case can really slow down the program,
	and by doing it this way it's doing it as efficient as possible.

	Having it public allows everyone to log a message into the external file.
	*/
	static void OnCreate(const std::string& name_ = "GAME258EngineLog");
	static void SetSeverity(MessageType type_);
	static void Info(const std::string& message_, const std::string& fileName_, const int line_);
	static void Trace(const std::string& message_, const std::string& fileName_, const int line_);
	static void Warning(const std::string& message_, const std::string& fileName_, const int line_);
	static void Error(const std::string& message_, const std::string& fileName_, const int line_);
	static void FatalError(const std::string& message_, const std::string& fileName_, const int line_);

private:

	/*
	Each of the 5 public functions for different types of log messages will call in
	the private log function.

	This private log function will have the functionality of writing to the file.
	*/
	static void Log(const std::string& message_, const std::string& fileName_, const int line_);
	static MessageType currentSev;

	/*
	File name for the debug file, it's a variable since we use it on the 
	OnCreaate and Log function.
	*/ 
	static std::string outputName; 


};






#endif // !DEBUG_H