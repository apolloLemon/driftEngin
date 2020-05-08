#ifndef PLAYER_H
#define PLAYER_H

// glm library
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"

#include "../camera/camOrt.h"

//#include "../meshes/cube.h"
#include "../shaders/shader.h"
//#include "../textures/texture.h"

#include "../utilities/phyx.h"
#include "gameObj.h"

const float PLAYER_SPEED = 2.5f;

enum Player_Movement {
	playerUP,
	playerDOWN,
	playerLEFT,
	playerRIGHT
};

class Player : public GameObj, public PhyxObj2D, public Model
{
public:

	Player(glm::vec3 position, std::string path);
	void draw(Shader *shader/*, Texture *texture*/);
	void ProcessKeyboard(Player_Movement direction, float deltaTime);

	CamOrt camera;
private:

};

#endif