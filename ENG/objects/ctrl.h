#ifndef INPUT_OBJ_H
#define INPUT_OBJ_H

#include "gameobj.h"

#include <GLFW/glfw3.h>
#include <iostream>

/*
enum of InputObj States
..I've just realised how an old friend coded his games
*/

class InputObj : public virtual GameObj
{
public:
	//interpret inputmsg for object
	virtual void inputCallback(GLFWwindow* window);
	virtual void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

class InputENG /*?: GameENG ?*/{
public:
	std::vector<InputObj*> managed;

	void Init(std::vector<GameObj*>*);
	void Update(GLFWwindow* window);
	void Update(GLFWwindow* window, int key, int scancode, int action, int mods);

};
#endif