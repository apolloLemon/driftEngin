#ifndef CAM_3RD_H
#define CAM_3RD_H

#include "camera.h"

class Cam3rd : public Camera
{
public:
	Cam3rd();

	void updateCameraVectors(glm::vec3 position, glm::vec3 direction);
};

#endif