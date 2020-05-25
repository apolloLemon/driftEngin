#ifndef FREECAM_H
#define FREECAM_H

#include "camera.h"

// Defines several possible options for camera movement. Used as absraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Freecam : public Camera
{
public:

	Freecam(	glm::vec3 position  = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 up 		= glm::vec3(0.0f, 1.0f, 0.0f),
				float yaw			= YAW,
				float pitch 		= PITCH
			);

	// Camera Options
	float MovementSpeed;
	float MouseSensitivity;

	void inputCallback(GLFWwindow* window) override;

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);

	void gui(GLFWwindow* window);

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();
};

#endif