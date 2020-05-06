#include "gameObj.h"

GameObject::GameObject(): worldPosition(glm::vec3(0.0f)), scale(glm::vec3(1.0f))
{

}

GameObject::GameObject(glm::vec3 wPos, glm::vec3 s): worldPosition(wPos), scale(s)
{

}