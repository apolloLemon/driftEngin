#ifndef CUBE_H
#define CUBE_H

#include "mesh.h"
#include "ENG/shaders/shader.h"

class Cube : public Mesh
{
public:
	Cube(std::vector<Texture> textures = std::vector<Texture>(), Material* material = nullptr);
};

#endif