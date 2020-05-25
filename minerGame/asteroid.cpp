#include "asteroid.h"

// Asteroid
// --------
Asteroid::Asteroid()
{
	this->position = glm::dvec3(0.0f);
}

// generate asteroid layers starting from a sphere, creating layers passing coordinates to the perlin object
void Asteroid::Generate(std::vector<Texture>* textures)
{
	core = Sphere(10, 10); // making a 10 by 10 sphere (121 vertices)

	maxLayer = rand() % 5 + 1; // making a random asteroid size between 1 and 5
	float extraperlinrand = (float)(rand() % 300 + 1); // perlin randomizer
	this->lifePoints = 50 * maxLayer; // lifePoints are based on the asteroid size

	// we generate each layer using perlin, starting from the sphere vertices
	std::vector<Vertex> layerVertices;
	Vertex layerVertex;
	for (unsigned int i = 0; i < maxLayer; i++)
	{
		layerVertices = std::vector<Vertex>();
		for (unsigned int j = 0; j < core.vertices.size(); j++)
		{
			layerVertex = core.vertices[j];
			layerVertex.Position *= (float)(i+1)*perlin.get(layerVertex.Position+extraperlinrand);
			layerVertices.push_back(layerVertex);
		}
		this->layers.push_back(layerVertices); // adding the layer to the asteroid layers
	}

	layerVertices = layers[maxLayer-1];

	this->meshes.push_back(new Mesh(layerVertices, core.indices, *textures)); // making the mesh to be the last layer

	// fill the active layer with the last layer's vertices, storing the corresponding layer number into each asteroidVertex
	AsteroidVertex astVertex;
	for (unsigned int i = 0; i < this->meshes[0]->vertices.size(); i++)
	{
		astVertex.layer = maxLayer;
		astVertex.vertex = this->meshes[0]->vertices[i];
		this->activeLayer.push_back(astVertex);
	}
	size = getMeanSize(); // initializing asteroid's size
}

// break a point from the active layer, replacing it by the corresponding point from the lower layer
void Asteroid::Break(unsigned int indice, GLFWwindow* window)
{
	if (activeLayer[indice].layer - 1 > 0) // decreasing the layer number
		activeLayer[indice].layer--;

	activeLayer[indice].vertex = this->layers[activeLayer[indice].layer-1][indice]; // changing the vertex to the corresponding one from the new layer

	std::vector<Vertex> vertices;
	bool changeMaxLayer = true;
	for (unsigned int i = 0; i < activeLayer.size(); i++)
	{
		if(activeLayer[i].layer == maxLayer) // if there's still a vertex from this layer
		{
			changeMaxLayer = false;
		}
		vertices.push_back(activeLayer[i].vertex); // creating a new vector of vertex to replace the active mesh
	}
	if (changeMaxLayer)	{ maxLayer--;}

	this->size = getMeanSize(); // updating the mean size
	this->lifePoints--; // decreasing lifepoints

	if(this->lifePoints <= 0) // if lifepoints go to zero
	{
		Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
		this->position.y -= 1000.0f; // the asteroid is moved far away, this way of making it disappear can be improved
		game->soundENG.Play(4, false); // playing the breaking asteroid sound effect
	}

	this->meshes[0] = new Mesh(vertices, this->meshes[0]->indices, this->meshes[0]->textures); // replacing the active mesh
}

float Asteroid::getMeanSize()
{
	float mean = 0.0f;
	for (unsigned int i = 0; i < activeLayer.size(); i++)
	{
		mean += glm::length(activeLayer[i].vertex.Position);
	}
	return (mean/activeLayer.size());
}

void Asteroid::gui(GLFWwindow* window)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

	ImGui::SetNextWindowPos(ImVec2(game->screenWidth/100.0f*5.0f, game->screenHeight/100.0f*20.0f));
	ImGui::Begin("Target", 0, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Position:");
	ImGui::Text("\tX:%.2f Y:%.2f Z:%.2f", this->worldPosition().x, this->worldPosition().y, this->worldPosition().z);
	ImGui::Text("\n");
	ImGui::Text("LifePoints: %i", this->lifePoints);
	ImGui::End();
}

// using poisson_disk_sampling, we generate, in a square, a set of positions, with a minimum distance between each other
std::vector<glm::vec3> generateAsteroidsPos(unsigned int& nb, const float radius, const float min, const float max)
{
	const auto kXMin = std::array<float, 2>	{{min, min}}; // lower-left square position
	const auto kXMax = std::array<float, 2>	{{max, max}}; // upper-right square position
	std::vector<std::array<float, 2>> positions = thinks::PoissonDiskSampling(radius, kXMin, kXMax); // returns a vector of 2-sized arrays {x, y}
	nb = positions.size();

	std::vector<glm::vec3> out;
	for (unsigned int i = 0; i < nb; i++)
	{
		// as our objects are place based on cooordinates x and z, with a y always at 0, we generate a vector (x, 0, z)
		out.push_back(glm::vec3(positions[i][0], 0.0f, positions[i][1]));
	}
	return out;
}

