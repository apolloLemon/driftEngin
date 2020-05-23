#include "player.h"
#include "ENG/objects/game.h"

Player::Player(glm::vec3 _position): MovementSpeed(PLAYER_SPEED)
{
	position = _position;
	Direction = glm::vec3(0.0f);
	camera.updateCameraVectors(worldPosition());
}


void Player::inputCallback(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if (game->cameraMode == ORTCAM_MODE)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		{ AddForce(glm::vec2(Direction.x, Direction.z)); }
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)		{ rotation.y += 1.0f; }
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)		{ AddForce(-glm::vec2(Direction.x, Direction.z)); }
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)		{ rotation.y -= 1.0f; }
	}

	Direction.x = sin(glm::radians(rotation.y));
	Direction.z = cos(glm::radians(rotation.y));
	Direction = glm::normalize(Direction);
}

void Player::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}
