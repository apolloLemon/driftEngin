#ifndef MESH_H
#define MESH_H

#include "includes/glad/glad.h"

#include "includes/glm/glm.hpp"
#include "includes/glm/matrix_transform.hpp"

#include "shaders/shader.h"

#include <string>
#include <vector>

struct Vertex
{
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangeant
	glm::vec3 Tangeant;
	// bitangeant
	glm::vec3 Bitangeant;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	// mesh data
	std::vector<Vertex>			vertices;
	std::vector<unsigned int>	indices;
	std::vector<Texture>		textures;
	unsigned int VAO;

	// constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	// render the mesh
	void Draw(Shader* shader);

private:
	// render data
	unsigned int VBO, EBO;

	// initialize all the buffer objects/arrays
	void setupMesh();
};

#endif