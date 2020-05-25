#include "freecam.h"
#include "ENG/objects/game.h"

Freecam::Freecam(glm::vec3 position, glm::vec3 up, float yaw, float pitch):
	Camera(position, up, yaw, pitch), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
{
	updateCameraVectors();
}

void Freecam::inputCallback(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if (game->cameraMode == FREECAM_MODE)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		{ Move(Front * 0.1f); }
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)		{ Move(Right * -0.1f); }
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)		{ Move(Front * -0.1f); }
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)		{ Move(Right * 0.1f); }
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)		{ Move(Up * 0.1f); }
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)		{ Move(Up * -0.1f); }
	}
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Freecam::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw 	+= xoffset;
	Pitch 	+= yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Freecam::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void Freecam::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right 	= glm::normalize(glm::cross(Front, WorldUp));
	Up 		= glm::normalize(glm::cross(Right, Front));
}

void Freecam::gui(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	ImGui::SetNextWindowPos(ImVec2(game->screenWidth/100.0f*90.0f, game->screenHeight/100.0f*20.0f), ImGuiCond_Always, ImVec2(0.5, 0.5));
	
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::Begin("Inputs", 0, window_flags);
	
	ImGui::Text("Inputs: ");
	ImGui::Text("\tZ: Move Forward");
	ImGui::Text("\tS: Move Backward");
	ImGui::Text("\tQ: Move Left");
	ImGui::Text("\tD: Move Right");
	ImGui::Text("\tR: Move Up");
	ImGui::Text("\tF: Move Down");
	ImGui::Text("\n");
	ImGui::Text("\tMouse movement: Rotate");
	ImGui::Text("\tMouse scroll: Zoom");
	ImGui::Text("\tN: Switch camera");

	ImGui::End();
}