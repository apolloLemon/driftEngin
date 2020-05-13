#include "asteroid.h"

Asteroid::Asteroid()
{

}

void Asteroid::Generate(std::vector<Texture> textures)
{
	core = Sphere(10, 10);

	srand(time(NULL));
	size = rand() % 5 + 1;

	std::vector<Vertex> layerVertices;
	Vertex layerVertex;
	for (unsigned int i = 0; i < size; i++)
	{
		layerVertices = std::vector<Vertex>();
		for (unsigned int j = 0; j < core.vertices.size(); j++)
		{
			layerVertex = core.vertices[j];
			layerVertex.Position *= (float)(i+1);
			layerVertices.push_back(layerVertex);
		}
		this->layers.push_back(layerVertices);
	}

	layerVertices = layers[size-1];

	Mesh layerMesh(layerVertices, core.indices, textures);

	this->meshes.push_back(layerMesh);

	AsteroidVertex astVertex;
	for (unsigned int i = 0; i < layerMesh.vertices.size(); i++)
	{
		astVertex.layer = size;
		astVertex.vertex = layerMesh.vertices[i];
		this->activeLayer.push_back(astVertex);
	}
}

void Asteroid::Break(unsigned int indice)
{
	if (activeLayer[indice].layer - 1 > 0)
		activeLayer[indice].layer--;

	unsigned int size = activeLayer[indice].layer;
	std::cout << size << std::endl;

	std::cout << "Before: [x:" << activeLayer[indice].vertex.Position.x << ", y:" << activeLayer[indice].vertex.Position.y << ", z:" << activeLayer[indice].vertex.Position.z << "]" << std::endl;
	activeLayer[indice].vertex = this->layers[size-1][indice];
	std::cout << "After: [x:" << this->layers[size-1][indice].Position.x << ", y:" << this->layers[size-1][indice].Position.y << ", z:" << this->layers[size-1][indice].Position.z << "]" << std::endl;

	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i < activeLayer.size(); i++)
	{
		vertices.push_back(activeLayer[i].vertex);
	}

	Mesh newLayer(vertices, this->meshes[0].indices, this->meshes[0].textures);

	this->meshes[0] = newLayer;
}