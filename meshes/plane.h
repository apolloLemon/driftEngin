#ifndef PLANE_H
#define PLANE_H

#include "mesh.h"
#include "textures/texture.h"
#include "shaders/shader.h"

class Plane : public Mesh
{
public:
	Plane(unsigned int xSegments, unsigned int ySegments);

	void draw(	glm::vec3 pos 		= glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec4 rot		= glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
				MODE mode			= MODE_NONE,
				Shader* shader 		= NULL,
				Texture* textures 	= NULL,
				int tex1			= 0,
				int tex2			= 0,
				float opacity		= 0.0f,
				glm::vec4 color		= glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) );
};

#endif