#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <vector>
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/gtc/matrix_transform.hpp"

/*
enum of GameObj States
*/


class GameObj
{
public:
	// Transformation variables
	glm::vec3 worldPosition;
	glm::vec3 scale;

	// constructors
	GameObj(); // default
	GameObj(glm::vec3 wPos, glm::vec3 scale);
	virtual ~GameObj()=default;
};


class Game {
public:
	std::vector<GameObj*> gameobjects;
//private:
};

#endif