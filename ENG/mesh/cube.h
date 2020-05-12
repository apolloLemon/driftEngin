#ifndef CUBE_H
#define CUBE_H

#include "mesh.h"
#include "ENG/shaders/shader.h"

class Cube : public Mesh
{
public:
	Cube(std::vector<Texture> textures);
	Cube(Material material);
};

#endif