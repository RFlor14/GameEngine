#include "Debug.h"

/*
Redeclare static variables at the top of cpp.

Format of re-declaring static variables:
1) Type of variable, [Debug::MessageType]

2) After the data type, variable name [Debug::currentSev], must always have call
the class name first with scope resolution operator.

3) Then whatever you want the variable to have as a default value [TYPE_NONE].
*/ 
Debug::MessageType Debug::currentSev = MessageType::TYPE_NONE;
std::string Debug::outputName = "";

/*
First thing we take in is the name given inside the header file or whatever
is typed in as a parameter to this function.

Add .txt (it's going to be a text file), helps to avoid confusion or mistakes.

[ofstream] is used to write to the debug file.

*/
void Debug::OnCreate(const std::string & name_)
{
	outputName = name_ + ".txt";
	std::ofstream out; //creates an ofstream variable called file

	/*
	Opens the file w/ the specific name of our output file.
	
	Must convert it to a char star, hence its called c_str function.

	It needs a mode, and we tell it that we are opening the file w/ the
	ability to write [std::ios::out] operation.
	*/ 
	out.open(outputName.c_str(), std::ios::out); 

	/*
	Close to create the file, doing it this way deletes everything inside the file
	and basically overwrites it.
	*/ 
	out.close(); 

	currentSev = MessageType::TYPE_INFO; // Sets the severity of the entire log manager to [TYPE_INFO].
}

/*
Adding in "[x ]: " will help finding the problem much easier when going through the file and 
help differentiate each of the Logs.
*/
void Debug::SetSeverity(MessageType type_)
{
	currentSev = type_; // Sets severity variable equal to type_
}

void Debug::Info(const std::string & message_, const std::string & fileName_, const int line_)
{
	Log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Debug::Trace(const std::string & message_, const std::string & fileName_, const int line_)
{
	Log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);
}

void Debug::Warning(const std::string & message_, const std::string & fileName_, const int line_)
{
	Log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);
}

void Debug::Error(const std::string & message_, const std::string & fileName_, const int line_)
{
	Log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debug::FatalError(const std::string & message_, const std::string & fileName_, const int line_)
{
	Log(MessageType::TYPE_FATAL_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debug::Log(const MessageType type_, const std::string & message_, const std::string & fileName_, const int line_)
{
	/*
	The order of the message type is very important, it goes from Fatal Error to least severity.

	1st part) if statement checks to see the specific type of message we want to log; if it's
	less than or equal to the current severity. It's essentially a filter.

	2nd part) A safety net to make sure we called our onCreate function, which
	check's if our current severity is greater than [TYPE_NONE]

	*/
	if (type_ <= currentSev && currentSev > MessageType::TYPE_NONE)
	{
		std::ofstream out;

		/*
		[std::ios::app] = Gives us the ability to append, which means you dont overwrite what
		is inside of the file, you just add to the end.

		[std::ios::out] = We're opening the file that gives us the abiility to write.
	
		*/
		out.open(outputName.c_str(), std::ios::app | std::ios::out);

		/*
		Name of the ofstream variable,
		the message,
		where you want to put the message in,
		what line that message is at,
		new line;
		*/
		out << message_ << " in: " << fileName_ << " on line: " << line_ << std::endl;
		out.flush(); // flushes the stream buffer before closing the output file.
		out.close();
	}
}


