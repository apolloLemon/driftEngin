#include "gameObj.h"

// initialize at pos 0,0,0 and at scale 1,1,1
GameObj::GameObj(): worldPosition(glm::vec3(0.0f)), scale(glm::vec3(1.0f))
{

}

GameObj::GameObj(glm::vec3 wPos, glm::vec3 s): worldPosition(wPos), scale(s)
{

}