#ifndef CAM_ORT_H
#define CAM_ORT_H

#include "camera.h"

class CamOrt : public Camera
{
public:
	CamOrt();
	void updateCameraVectors(glm::vec3 pos);

private:
};

#endif