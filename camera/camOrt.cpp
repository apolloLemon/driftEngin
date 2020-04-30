#include "camOrt.h"

// Constructor with vectors
CamOrt::CamOrt(glm::vec3 position):
	Camera(position, glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -90.0f), MovementSpeed(SPEED)
{
	Front = glm::vec3(0.0f, -1.0f, 0.0f);
	updateCameraVectors();
}

void CamOrt::ProcessKeyboard(CamOrt_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == ortUP)
		Position.z += velocity;
	if (direction == ortDOWN)
		Position.z -= velocity;
	if (direction == ortLEFT)
		Position.x += velocity;
	if (direction == ortRIGHT)
		Position.x -= velocity;
}

void CamOrt::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right 	= glm::normalize(glm::cross(Front, WorldUp));
	Up 		= glm::normalize(glm::cross(Right, Front));
}