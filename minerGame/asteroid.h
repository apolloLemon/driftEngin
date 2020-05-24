#ifndef ASTEROID_H
#define ASTEROID_H

#include "ENG/mesh/sphere.h"

#include "ENG/objects/phyx.h"
#include "ENG/objects/kldr.h"
#include "ENG/objects/ctrl.h"
#include "ENG/objects/rndr.h"
#include "ENG/objects/perlin.h"

#include "ENG/includes/poisson_disk_sampling/poisson_disk_sampling.h"

#include <ctime>
#include <cstdlib>

std::vector<glm::vec3> generateAsteroidsPos(unsigned int&, float, float, float);

struct AsteroidVertex
{
	unsigned int layer;
	Vertex vertex;
};

class Asteroid : public RenderObj, public PhyxObj2D//, public CollisionObj //PhyxObj is one.. for now
{
public:
	Sphere core;
	unsigned int maxLayer;
	std::vector<std::vector<Vertex>> layers;
	std::vector<AsteroidVertex> activeLayer;
	Perlin3D perlin;

	Asteroid();
	void Generate(std::vector<Texture>* textures);
	void Break(unsigned int indice);
	float size();

};

#endif