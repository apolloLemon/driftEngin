#ifndef ASTEROID_H
#define ASTEROID_H

// including what we need from our engine
#include "ENG/mesh/sphere.h"
#include "ENG/objects/game.h"
#include "ENG/objects/phyx.h"
#include "ENG/objects/kldr.h"
#include "ENG/objects/ctrl.h"
#include "ENG/objects/rndr.h"
#include "ENG/objects/perlin.h"
#include "ENG/includes/poisson_disk_sampling/poisson_disk_sampling.h"

#include <ctime> // used for time()
#include <cstdlib> // used for rand()

std::vector<glm::vec3> generateAsteroidsPos(unsigned int&, float, float, float); // generates asteroid positions with poisson_disk_sampling

// Asteroid
// --------
struct AsteroidVertex
{
	unsigned int layer; // the layer number
	Vertex vertex; // vertex informations
};

class Asteroid : public RenderObj, public PhyxObj2D
{
public:
	Sphere core; // the sphere used to generate the asteroid
	unsigned int maxLayer; // storing the maximum layer of the asteroid
	float size; // used to generate a collider
	int lifePoints;
	std::vector<std::vector<Vertex>> layers; // used to store every vertex of each layer
	std::vector<AsteroidVertex> activeLayer; // our active layer, which will be drawn
	Perlin3D perlin; // perlin object to use perlin noise

	// constructor
	Asteroid();
	// asteroid functions
	void Generate(std::vector<Texture>* textures);
	void Break(unsigned int indice, GLFWwindow* window); // break a given point
	float getMeanSize(); // returns a size based on the mean length of its radiuses
	// gui function
	void gui(GLFWwindow*);

};

#endif