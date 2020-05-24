#include "asteroid.h"

Asteroid::Asteroid()
{
	this->position = glm::dvec3(0.0f);
}

void Asteroid::Generate(std::vector<Texture>* textures)
{
	core = Sphere(10, 10);

	maxLayer = rand() % 5 + 1;

	std::vector<Vertex> layerVertices;
	Vertex layerVertex;
	//perlin.gen(5, 1, 1);
	bool b=false;
	for (unsigned int i = 0; i < maxLayer; i++)
	{
		layerVertices = std::vector<Vertex>();
		for (unsigned int j = 0; j < core.vertices.size(); j++)
		{
			layerVertex = core.vertices[j];
			if(b)std::cout << layerVertex.Position.x <<"\t"<< layerVertex.Position.y <<"\t"<< layerVertex.Position.z <<"\n";  
			layerVertex.Position *= (float)(i+1)*perlin.get(layerVertex.Position);
			layerVertices.push_back(layerVertex);
		}
		this->layers.push_back(layerVertices);
		b=false;
	}

	layerVertices = layers[maxLayer-1];

	this->meshes.push_back(new Mesh(layerVertices, core.indices, *textures));

	AsteroidVertex astVertex;
	for (unsigned int i = 0; i < this->meshes[0]->vertices.size(); i++)
	{
		astVertex.layer = maxLayer;
		astVertex.vertex = this->meshes[0]->vertices[i];
		this->activeLayer.push_back(astVertex);
	}
}

void Asteroid::Break(unsigned int indice)
{
	if (activeLayer[indice].layer - 1 > 0)
		activeLayer[indice].layer--;

	unsigned int maxLayer = activeLayer[indice].layer;
	//std::cout << maxLayer << std::endl;

	//std::cout << "Before: [x:" << activeLayer[indice].vertex.Position.x << ", y:" << activeLayer[indice].vertex.Position.y << ", z:" << activeLayer[indice].vertex.Position.z << "]" << std::endl;
	activeLayer[indice].vertex = this->layers[maxLayer-1][indice];
	//std::cout << "After: [x:" << this->layers[maxLayer-1][indice].Position.x << ", y:" << this->layers[maxLayer-1][indice].Position.y << ", z:" << this->layers[maxLayer-1][indice].Position.z << "]" << std::endl;

	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i < activeLayer.size(); i++)
	{
		vertices.push_back(activeLayer[i].vertex);
	}

	this->meshes[0] = new Mesh(vertices, this->meshes[0]->indices, this->meshes[0]->textures);
}

float Asteroid::size()
{
	int point = rand() % this->activeLayer.size();
	return glm::length(activeLayer[point].vertex.Position);
}

std::vector<glm::vec3> generateAsteroidsPos(unsigned int& nb, const float radius, const float min, const float max)
{
	const auto kXMin = std::array<float, 2>	{{min, min}};
	const auto kXMax = std::array<float, 2>	{{max, max}};
	std::vector<std::array<float, 2>> positions = thinks::PoissonDiskSampling(radius, kXMin, kXMax);
	nb = positions.size();

	std::vector<glm::vec3> out;
	for (unsigned int i = 0; i < nb; i++)
	{
		out.push_back(glm::vec3(positions[i][0], 0.0f, positions[i][1]));
	}
	return out;
}