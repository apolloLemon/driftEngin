#include "gameobj.h"

// initialize at pos 0,0,0 and at scale 1,1,1
GameObj::GameObj(): position(glm::vec3(0.0f)), scale(glm::vec3(1.0f)), rotation(glm::vec3(0.0f))
{
	parent = nullptr;
}

GameObj::GameObj(glm::vec3 wPos, glm::vec3 s): position(wPos), scale(s)
{

}