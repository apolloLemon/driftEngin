#include "player.h"
#include "ENG/objects/game.h"

Player::Player(glm::vec3 _position): MovementSpeed(PLAYER_SPEED)
{
	position = _position;
	Direction = glm::vec3(0.0f);
	thrusting = false;
	camera.updateCameraVectors(worldPosition());
}


void Player::inputCallback(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if (game->cameraMode == ORTCAM_MODE)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	{ AddForce(glm::dvec2(Direction.x, Direction.z)*2.); }
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	{ rotation.y += 1.3f; }
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	{ AddForce(-glm::dvec2(Direction.x, Direction.z)); }
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	{ rotation.y -= 1.3f; }
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	{ AddForce(glm::dvec2(-Direction.z, Direction.x)); }
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	{ AddForce(glm::dvec2(Direction.z, -Direction.x)); }
	}

	Direction.x = sin(glm::radians(rotation.y));
	Direction.z = cos(glm::radians(rotation.y));
	Direction = glm::normalize(Direction);
}

void Player::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if (game->cameraMode == ORTCAM_MODE)
	{
		if (key == GLFW_KEY_W && action == GLFW_PRESS)	{ if(!thrusting) { thrusting = true; game->soundENG.Play(5, true, 0.1f); } }
		if (key == GLFW_KEY_S && action == GLFW_PRESS)	{ if(!thrusting) { thrusting = true; game->soundENG.Play(5, true, 0.1f); } }
		if (key == GLFW_KEY_E && action == GLFW_PRESS)	{ if(!thrusting) { thrusting = true; game->soundENG.Play(5, true, 0.1f); } }
		if (key == GLFW_KEY_D && action == GLFW_PRESS)	{ if(!thrusting) { thrusting = true; game->soundENG.Play(5, true, 0.1f); } }
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)	{ if(thrusting) { thrusting = false; game->soundENG.Stop(5); } }
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)	{ if(thrusting) { thrusting = false; game->soundENG.Stop(5); } }
		if (key == GLFW_KEY_E && action == GLFW_RELEASE)	{ if(thrusting) { thrusting = false; game->soundENG.Stop(5); } }
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)	{ if(thrusting) { thrusting = false; game->soundENG.Stop(5); } }
	}
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
		game->soundENG.Play(3, false, 0.1f);
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