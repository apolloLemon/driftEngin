#include "player.h"
#include "ENG/objects/game.h"

// Player
// ------
Player::Player(): thrusting(false), target(nullptr), score(0)
{
	// initialize player's direction based on its rotation
	Direction.x = sin(glm::radians(rotation.y));
	Direction.z = cos(glm::radians(rotation.y));
	Direction = glm::normalize(Direction); // normalizing the vector, just for safety
	// update the player's camera vectors
	camera.updateCameraVectors(worldPosition());
}

// input function, used for long keyboard press
void Player::inputCallback(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window)); // casting the user pointer from our GLFWwindow
	// configure player's movements
	if (game->cameraMode == ORTCAM_MODE)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	{ AddForce(glm::dvec2(Direction.x, Direction.z)*2.); }
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	{ rotation.y += 1.3f; }
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	{ AddForce(-glm::dvec2(Direction.x, Direction.z)); }
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	{ rotation.y -= 1.3f; }
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	{ AddForce(glm::dvec2(-Direction.z, Direction.x)); }
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	{ AddForce(glm::dvec2(Direction.z, -Direction.x)); }
	}
	// update the direction vector
	Direction.x = sin(glm::radians(rotation.y));
	Direction.z = cos(glm::radians(rotation.y));
	Direction = glm::normalize(Direction);
}

// input function, used for simple keyboard press
void Player::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	// configure inputs for player thruster's sound effect
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

	// formatting the score to be a string, separating thousands (10000 -> 10,000)
	std::ostringstream ss;
	ss.imbue(std::locale("en_US.UTF-8"));
	ss << this->score;

	// player informations window
	// --------------------------
	ImGui::SetNextWindowPos(ImVec2(game->screenWidth/100.0f*5.0f, game->screenHeight/100.0f*5.0f)); // window position based on screen size
	ImGui::Begin("Player", 0, ImGuiWindowFlags_AlwaysAutoResize); // creating a window with an auto-resize flag
	ImGui::Text("Position:");
	ImGui::Text("\tX:%.2f Y:%.2f Z:%.2f", this->worldPosition().x, this->worldPosition().y, this->worldPosition().z);
	ImGui::Text("Direction:");
	ImGui::Text("\tX:%.2f Y:%.2f Z:%.2f", this->Direction.x, this->Direction.y, this->Direction.z);
	ImGui::End(); // ending the window filling

	// score window
	// ------------
	ImGuiWindowFlags window_flags = 0; // adding multiple window flags
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::SetNextWindowPos(ImVec2(game->screenWidth/100.0f*50.0f, game->screenHeight/100.0f*5.0f), ImGuiCond_Always, ImVec2(0.5, 0.5)); // the last parameters center the window to the position
	ImGui::Begin("Score", 0, window_flags);
	ImGui::SetWindowFontScale(1.5f); // changing the font size
	ImGui::Text(("Score: " + ss.str()).c_str());	
	ImGui::End();

	// inputs informations window
	// --------------------------
	ImGui::SetNextWindowPos(ImVec2(game->screenWidth/100.0f*90.0f, game->screenHeight/100.0f*20.0f), ImGuiCond_Always, ImVec2(0.5, 0.5));
	ImGui::Begin("Inputs", 0, window_flags);
	ImGui::Text("Inputs: ");
	ImGui::Text("\tZ: Move Forward");
	ImGui::Text("\tS: Move Backward");
	ImGui::Text("\tQ: Rotate Left");
	ImGui::Text("\tD: Rotate Right");
	ImGui::Text("\tA: Move Left");
	ImGui::Text("\tE: Move Right");
	ImGui::Text("\n");
	ImGui::Text("\tMouse scroll: Zoom");
	ImGui::Text("\tN: Switch camera");
	ImGui::Text("\n");
	ImGui::Text("\tECHAP: Exit game");
	ImGui::End();
}

// Shield
// ------
Shield::Shield(float size): lifePoints(100)
{
	this->size = size;
	animation.isAnimating = false;
}

void Shield::startAnimation(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if(!animation.isAnimating)
	{
		animation.isAnimating = true;
		animation.start = glfwGetTime(); // setting the animation starting time
		game->soundENG.Play(3, false, 0.1f); // play sound effect with a 0.1f volume
	}
}

void Shield::Update(GLFWwindow* window)
{
	if(animation.isAnimating) // if the shield is animating
	{
		Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
		Draw(game->textureShader); // draw the shield
		if((glfwGetTime() - animation.start) > 0.2f) // once it's been more thans 0.2 secondes, stop the animation
		{
			animation.isAnimating = false;
		}
	}
}

void Shield::gui(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	ImGui::SetNextWindowPos(ImVec2(game->screenWidth/100.0f*50.0f, game->screenHeight/100.0f*80.0f));
	ImGui::Begin("Shield", 0, window_flags);
	ImGui::Text("Auto mining...");
	ImGui::End();
}