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

Shield::Shield(float size)
{
	this->size = size;
	lifePoints = 100;
	animation.isAnimating = false;
}

void Shield::startAnimation(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if(!animation.isAnimating)
	{
		animation.isAnimating = true;
		animation.start = glfwGetTime();
		game->soundENG.Play(3, false);
	}
}

void Shield::Update(GLFWwindow* window)
{
	if(animation.isAnimating)
	{
		Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
		Draw(game->textureShader);
		if((glfwGetTime() - animation.start) > 0.2f)
		{
			animation.isAnimating = false;
			return;
		}
	}
}