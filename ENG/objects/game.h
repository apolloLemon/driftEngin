#ifndef GAME_H
#define GAME_H

// Simple process to switch between Matthew's and Nathan's directories
// -------------------------------------------------------------------
#define PWD "/home/rakl/Repository/spaceProject/driftEngin/"
//#define PWD "/home/melon/driftEngin/"

//* Imgui 1/4
#include "ENG/includes/imgui/imgui.h"
#include "ENG/includes/imgui/imgui_impl_glfw.h"
#include "ENG/includes/imgui/imgui_impl_opengl3.h"
//*/


#include "ENG/includes/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

#include "ENG/includes/glm/glm.hpp"

#include "ENG/objects/gameobj.h"
#include "ENG/objects/phyx.h"
#include "ENG/objects/ctrl.h"
#include "ENG/objects/rndr.h"

#include "ENG/shaders/shader.h"

#include "ENG/camera/freecam.h"

#include "drift/player.h"


enum CameraMode
{
	FREECAM_MODE,
	ORTCAM_MODE,
	THIRDCAM_MODE
};


class Game
{
public:
	std::vector<GameObj*> gameobjects;

	// Camera
	Camera* currentCamera;
	Freecam* freecam;
	CameraMode cameraMode;

	// Shaders
	Shader* textureShader;
	Shader* materialShader;
	Shader* lightSourceShader;
	Shader* skyboxShader;

	// Window informations
	unsigned int screenWidth;
	unsigned int screenHeight;
	float lastX;
	float lastY;
	bool firstMouse;

	// Engines
	RenderENG rndrENG;
	PhyxENG phyxENG;
	InputENG inputENG;

	// Path Variables
	std::string srcPath;
	std::string vShadersPath;
	std::string fShadersPath;
	std::string texturesPath;
	std::string modelsPath;

	Game(unsigned int width, unsigned int height, std::string tPath, std::string mPath);
	GLFWwindow* Initialize();
	void displayImGui();
	void Terminate();
};

// GLFW callback functions
// ------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif