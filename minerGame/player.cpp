#include "player.h"
#include "ENG/objects/game.h"

Player::Player(glm::vec3 _position): MovementSpeed(PLAYER_SPEED)
{
	position = _position;
	Direction = glm::vec3(0.0f);
	thrusting = false;
	target = nullptr;
	score = 0;
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
		if (key == GLFW_KEY_W && action == GLFW_PRESS)	{ if(!thrusting) { thrusting = true; game->soundENG.Play(5, true, 0.2f); } }
		if (key == GLFW_KEY_S && action == GLFW_PRESS)	{ if(!thrusting) { thrusting = true; game->soundENG.Play(5, true, 0.2f); } }
		if (key == GLFW_KEY_E && action == GLFW_PRESS)	{ if(!thrusting) { thrusting = true; game->soundENG.Play(5, true, 0.2f); } }
		if (key == GLFW_KEY_Q && action == GLFW_PRESS)	{ if(!thrusting) { thrusting = true; game->soundENG.Play(5, true, 0.2f); } }
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)	{ if(thrusting) { thrusting = false; game->soundENG.Stop(5); } }
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)	{ if(thrusting) { thrusting = false; game->soundENG.Stop(5); } }
		if (key == GLFW_KEY_E && action == GLFW_RELEASE)	{ if(thrusting) { thrusting = false; game->soundENG.Stop(5); } }
		if (key == GLFW_KEY_Q && action == GLFW_RELEASE)	{ if(thrusting) { thrusting = false; game->soundENG.Stop(5); } }
	}
}

void Player::gui(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

	std::ostringstream ss;
	ss.imbue(std::locale("en_US.UTF-8"));
	ss << this->score;

	ImGui::SetNextWindowPos(ImVec2(game->screenWidth/100.0f*5.0f, game->screenHeight/100.0f*5.0f));
	ImGui::Begin("Player", 0, ImGuiWindowFlags_AlwaysAutoResize);
	
	ImGui::Text("Position:");
	ImGui::Text("\tX:%.2f Y:%.2f Z:%.2f", this->worldPosition().x, this->worldPosition().y, this->worldPosition().z);
	ImGui::Text("\n");
	ImGui::Text(("Score: " + ss.str()).c_str());	

	ImGui::End();
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

void Shield::gui(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

	//ImGui::SetNextWindowSize(ImVec2(game->screenWidth/5.0f, game->screenHeight/10.0f));
	ImGui::SetNextWindowPos(ImVec2(game->screenWidth/100.0f*50.0f, game->screenHeight/100.0f*80.0f));

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	ImGui::Begin("Shield", 0, window_flags);
	
	ImGui::Text("Auto mining...");

	ImGui::End();
}