#ifndef CAM_ORT_H
#define CAM_ORT_H

#include "camera.h"

enum CamOrt_Movement {
	ortUP,
	ortDOWN,
	ortLEFT,
	ortRIGHT
};

class CamOrt : public Camera
{
public:
	CamOrt(glm::vec3 position);

	float MovementSpeed;

	void ProcessKeyboard(CamOrt_Movement direction, float deltaTime);

private:
	void updateCameraVectors();
};

#endif