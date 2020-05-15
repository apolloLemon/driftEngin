#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <vector>
#include <string>

#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/gtc/matrix_transform.hpp"

/*
enum of GameObj States
*/

class GameObj
{
public:
	std::string name;
	// Transformation variables
	glm::vec3 worldPosition;
	glm::vec3 scale;
	glm::vec3 rotation; // Picth / Yaw / Roll

	// constructors
	GameObj(); // default
	GameObj(glm::vec3 wPos, glm::vec3 scale);
	virtual ~GameObj()=default;
};

#endif