#include "Game1.h"


// When inheriting, make sure to declare the constructor of the parent class
Game1::Game1() : GameInterface()
{
}


Game1::~Game1()
{
}

bool Game1::OnCreate()
{
	return true;
}

void Game1::Update(const float deltaTime_)
{
}

void Game1::Render()
{
}
