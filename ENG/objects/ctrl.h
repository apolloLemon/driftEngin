#ifndef INPUT_OBJ_H
#define INPUT_OBJ_H

#include "game.h"

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
	virtual void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

class InputENG /*?: GameENG ?*/{
	//table of input to input(msg/event)
	//table of default input to input(msg/event) (window stuff)
};
#endif