#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

#include "ENG/camera/camera.h"
#include "ENG/objects/gameobj.h"

struct CameraMode
{
	FREE_CAM,
	ORT_CAM,
	THIRD_CAM
};


class Game
{
public:
	std::vector<GameObj*> gameobjects;
	Camera* currentCamera;
	CameraMode cameraMode;

	GLFWwindow* Initialize();
};



#endif