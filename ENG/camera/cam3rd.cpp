#include "cam3rd.h"

// Constructor with vectors
Cam3rd::Cam3rd() : Camera()
{

}

// Calculates the front vector from the Camera's (updated) Eular Angles
void Cam3rd::updateCameraVectors(glm::vec3 pos, glm::vec3 dir)
{
	glm::vec3 newPos = pos - 4.0f*dir;
	worldPosition = glm::vec3(newPos.x, newPos.y + 1.5f, newPos.z);
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = dir.x;
	front.y = -0.2f;
	front.z = dir.z;
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right 	= glm::normalize(glm::cross(Front, WorldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up 		= glm::normalize(glm::cross(Right, Front));
}