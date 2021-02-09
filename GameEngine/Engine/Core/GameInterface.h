#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface
{
public:

	// Declared and Empty
	GameInterface() {}
	virtual ~GameInterface() {}

	/*
	Basic functions that a game needs to have, since they are abstract class,
	they are virtual and equals zero. 
	
	Meaning the definition is not made here, and the child class has to define
	all three of these functions.
	*/ 
	virtual bool onCreate() = 0; 
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
};


#endif // !GAMEINTERFACE_H





