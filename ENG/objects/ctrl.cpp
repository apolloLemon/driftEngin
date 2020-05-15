#include "ctrl.h"

void InputObj::inputCallback(GLFWwindow* window)
{

}

void InputObj::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void InputENG::Init(std::vector<GameObj*>* gameobjects)
{
	managed.clear();
	for (unsigned int i = 0; i < gameobjects->size(); i++)
	{
		GameObj* go = gameobjects->at(i);
		InputObj* cast = dynamic_cast<InputObj *>(go);
		if(cast)	managed.push_back(cast);
	}
}

void InputENG::Update(GLFWwindow* window)
{
	for (auto obj : managed)
	{
		obj->inputCallback(window);
	}
}

void InputENG::Update(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (auto obj : managed)
	{
		obj->inputCallback(window, key, scancode, action, mods);
	}
}