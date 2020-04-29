#include "mesh.h"

Mesh::Mesh()
{

}

void Mesh::Finalize()
{
	// initiialize object IDs if not configured before
	if (!m_VAO)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
	}

	// preprocess buffer data as interleaved or separate when specified
	std::vector<float> data;

	for (int i = 0; i < Positions.size(); ++i)
	{
		data.push_back(Positions[i].x);
		data.push_back(Positions[i].y);
		data.push_back(Positions[i].z);

		if(UV.size() > 0)
		{
			data.push_back(UV[i].x);
			data.push_back(UV[i].y);
		}
		if(Normals.size() > 0)
		{
			data.push_back(Normals[i].x);
			data.push_back(Normals[i].y);
			data.push_back(Normals[i].z);
		}
	}

	// configure vertex attributes (only on vertex data size() > 0)
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	// only fill with the index buffer if the index array is non-empty
	if (Indices.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);
	}

	size_t stride					= 3 * sizeof(float);
	if (UV.size() > 0)		stride += 2 * sizeof(float);
	if (Normals.size() > 0) stride += 3 * sizeof(float);

	size_t offset = 0;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 3 * sizeof(float);

	if (UV.size() > 0)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 2 * sizeof(float);
	}
	if (Normals.size() > 0)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	}

	glBindVertexArray(0);
}