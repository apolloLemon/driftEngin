#ifndef CUBE_H
#define CUBE_H

#include "mesh.h"
#include "shaders/shader.h"

class Cube : public Mesh
{
public:
	Cube(std::vector<Texture> textures = std::vector<Texture>());
};

#endif