#ifndef MESH_H
#define MESH_H

#include "includes/glad/glad.h"

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"

#include "includes/stb_image/stb_image.h"

#include "shaders/shader.h"

#include "gameobjects/gameObj.h"

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

class Mesh : virtual public GameObj
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
	void Draw(Shader* shader);
	// initialize all the buffer objects/arrays
	void setupMesh();

private:
	// render data
	unsigned int VBO, EBO;
	
};

#endif