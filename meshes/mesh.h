#ifndef MESH_H
#define MESH_H

#include "includes/glad/glad.h"
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"

#include <vector>

enum MODE
{
	MODE_TEX2,
	MODE_TEX1,
	MODE_COLOR,
	MODE_NONE
};

class Mesh
{
public:
	unsigned int m_VAO = 0;
	unsigned int m_VBO;
	unsigned int m_EBO;

	std::vector<glm::vec3> Positions; 	// This is the vertices positions vector
	std::vector<glm::vec2> UV;			// This is the texture coords vector
	std::vector<glm::vec3> Normals;		// This is the normals coords vector, unused for now

	std::vector<unsigned int> Indices;

	Mesh();

	void Finalize();
};

#endif