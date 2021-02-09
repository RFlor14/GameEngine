#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:

	// Declared and Empty
	Scene() {}
	virtual ~Scene() {}

	/*
	Basic functions that a game needs to have, since they are abstract class,
	they are virtual and equals zero.

	Meaning the definition is not made here, and the child class has to define
	all three of these functions.
	*/
	virtual bool OnCreate() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
};


#endif // !SCENE_H



