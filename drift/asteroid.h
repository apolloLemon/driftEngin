#pragma once
#ifndef ASTEROID_MESH_H
#define ASTEROID_MESH_H

#include "ENG/mesh/sphere.h"

#include "ENG/objects/phyx.h"
#include "ENG/objects/kldr.h"
#include "ENG/objects/ctrl.h"
#include "ENG/objects/rndr.h"
#include "ENG/objects/perlin.h"

#include <ctime>
#include <cstdlib>

struct AsteroidVertex
{
	unsigned int layer;
	Vertex vertex;
};

class Asteroid : public RenderObj, public PhyxObj2D, public CollisionObj
{
public:
	Sphere core;
	unsigned int size;
	std::vector<std::vector<Vertex>> layers;
	std::vector<AsteroidVertex> activeLayer;
	Perlin3D perlin;

	Asteroid();
	void Generate(std::vector<Texture> textures);
	void Break(unsigned int indice);

};

#endif