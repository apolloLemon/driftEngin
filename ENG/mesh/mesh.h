#ifndef MESH_H
#define MESH_H

#include "ENG/includes/glad/glad.h"
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/gtc/matrix_transform.hpp"
#include "ENG/includes/stb_image/stb_image.h"

#include "ENG/shaders/shader.h"

#include "ENG/objects/game.h"

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
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path; // we store the path of the texture to compare with other textures
};

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);

class Mesh
{
public:
	// mesh data
	std::vector<Vertex>			vertices;
	std::vector<unsigned int>	indices;
	std::vector<Texture>		textures;
	Material*					material;

	unsigned int VAO;

	// constructors
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material *material = nullptr);
	// render the mesh
	void Draw(Shader* shader, glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
	// initialize all the buffer objects/arrays
	void setupMesh();

private:
	// render data
	unsigned int VBO, EBO;
	
};

#endif