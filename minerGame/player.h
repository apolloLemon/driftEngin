#ifndef PLAYER_H
#define PLAYER_H

// glm library
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/gtc/matrix_transform.hpp"

#include "ENG/camera/camOrt.h"

#include "ENG/shaders/shader.h"
#include "ENG/model/model.h"

#include "ENG/objects/phyx.h"
#include "ENG/objects/kldr.h"
#include "ENG/objects/ctrl.h"
#include "ENG/objects/rndr.h"

const float PLAYER_SPEED = 2.5f;

enum Player_Movement {
	playerUP,
	playerDOWN,
	playerLEFT,
	playerRIGHT
};

class Player : public PhyxObj2D, public InputObj, public RenderObj
{
public:

	CamOrt camera;
	float MovementSpeed;
	glm::vec3 Direction;
	bool thrusting;

	Player(glm::vec3 position = glm::vec3(0.0f));
	//void draw(Shader *shader);
	void inputCallback(GLFWwindow* window) override;
	void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

private:

};

struct Animation
{
	bool isAnimating;
	float start;
};

class Shield : public PhyxObj2D, public RenderObj
{
public:
	float size;
	int lifePoints;
	Animation animation;

	Shield(float);
	void startAnimation(GLFWwindow* window);
	void Update(GLFWwindow* window);
};

#endif