#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"

#include <vector>
#include <iostream>

// Default camera values
const float YAW			= -90.0f;
const float PITCH		=  -30.0f;
const float SPEED		=   2.5f;
const float SENSITIVITY =   0.1f;
const float ZOOM		=  45.0f;

// An abstract camera class that processes and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	//Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Euler Angles
	float Yaw;
	float Pitch;
	float Zoom;

	// Constructor with vectors
	Camera(	glm::vec3 position 	= glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up 		= glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw 			= YAW,
			float pitch 		= PITCH);

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

};

#endif
