#include "camOrt.h"

// Constructor with vectors
CamOrt::CamOrt():
	Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -90.0f)
{
	Front = glm::vec3(0.0f, -1.0f, 0.0f);
	updateCameraVectors(glm::vec3(0.0f));
}

void CamOrt::updateCameraVectors(glm::vec3 pos)
{
	worldPosition = glm::vec3(pos.x, pos.y + 95.0f, pos.z);
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right 	= glm::normalize(glm::cross(Front, WorldUp));
	Up 		= glm::normalize(glm::cross(Right, Front));
}

void CamOrt::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}