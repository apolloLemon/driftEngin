#ifndef PLAYER_H
#define PLAYER_H

// glm library
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"

#include "camera/camOrt.h"

#include "shaders/shader.h"
#include "model/model.h"

#include "objects/phyxObj.h"
#include "objects/collisionObj.h"
#include "objects/inputObj.h"
#include "objects/renderObj.h"

const float PLAYER_SPEED = 2.5f;

enum Player_Movement {
	playerUP,
	playerDOWN,
	playerLEFT,
	playerRIGHT
};

class Player : public PhyxObj2D, public CollisionObj, public InputObj, public RenderObj
{
public:

	CamOrt camera;
	float MovementSpeed;

	Player(glm::vec3 position = glm::vec3(0.0f));
	//void draw(Shader *shader);
	void ProcessKeyboard(Player_Movement direction, float deltaTime);

private:

};

#endif