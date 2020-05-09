#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Zoom(ZOOM)
{
	worldPosition = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(worldPosition, worldPosition + Front, Up);
}