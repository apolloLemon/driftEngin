#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

const float PI 	= 3.14159265359f;
const float TAU	= 6.28318530717f;

class Sphere : public Mesh
{
public:
	Sphere(unsigned int xSegments, unsigned int ySegments, std::vector<Texture> textures = std::vector<Texture>(), Material* material = nullptr);
};

#endif