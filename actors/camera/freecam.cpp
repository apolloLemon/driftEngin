#include "freecam.h"

Freecam::Freecam(glm::vec3 position, glm::vec3 up, float yaw, float pitch):
	Camera(position, up, yaw, pitch), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
{
	updateCameraVectors();
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Freecam::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		worldPosition += Front * velocity;
	if (direction == BACKWARD)
		worldPosition -= Front * velocity;
	if (direction == LEFT)
		worldPosition -= Right * velocity;
	if (direction == RIGHT)
		worldPosition += Right * velocity;
	if (direction == DOWN)
		worldPosition -= Up * velocity;
	if (direction == UP)
		worldPosition += Up * velocity;
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