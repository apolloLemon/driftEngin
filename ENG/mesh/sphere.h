#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

const float PI 	= 3.14159265359f;
const float TAU	= 6.28318530717f;

class Sphere : public Mesh
{
public:
	Sphere();
	Sphere(unsigned int xSegments, unsigned int ySegments);
	Sphere(unsigned int xSegments, unsigned int ySegments, Material material);
	Sphere(unsigned int xSegments, unsigned int ySegments, std::vector<Texture> textures);
};

#endif