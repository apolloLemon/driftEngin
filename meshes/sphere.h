#ifndef MESH_SPHERE_H
#define MESH_SPHERE_H

#include "mesh.h"

class Sphere : public Mesh
{
public:
	Sphere(unsigned int xSegments, unsigned int ySegments);
};

#endif