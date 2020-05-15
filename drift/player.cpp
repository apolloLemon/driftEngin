#include "player.h"
#include "ENG/objects/game.h"

Player::Player(glm::vec3 position): MovementSpeed(PLAYER_SPEED)
{
	worldPosition = position;
	camera.updateCameraVectors(worldPosition);
}


void Player::inputCallback(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if (game->cameraMode == ORTCAM_MODE)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		{ AddForce(glm::vec2( 0,  1)); }
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)		{ AddForce(glm::vec2( 1,  0)); }
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)		{ AddForce(glm::vec2( 0, -1)); }
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)		{ AddForce(glm::vec2(-1,  0)); }
	}
}

void Player::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}
