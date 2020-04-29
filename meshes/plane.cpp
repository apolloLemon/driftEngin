#include "plane.h"

Plane::Plane(unsigned int xSegments, unsigned int ySegments)
{
	bool oddRow = false;

	float dX = 1.0f / xSegments;
	float dY = 1.0f / ySegments;

	for (int y = 0; y <= ySegments; ++y)
	{
		for (int x = 0; x <= xSegments; ++x)
		{
			Positions.push_back(glm::vec3(dX * x * 2.0f - 1.0f, dY * y * 2.0f - 1.0f, 0.0f));
			UV.push_back(glm::vec2(dX * x, dY * y));
			Normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}

	for (int y = 0; y < ySegments; ++y)
	{
		for (int x = 0; x < xSegments; ++x)
		{
			Indices.push_back(  y   * (xSegments+1) + x);
			Indices.push_back((y+1) * (xSegments+1) + x);
			Indices.push_back(  y   * (xSegments+1) + x + 1);
			Indices.push_back(  y   * (xSegments+1) + x + 1);
			Indices.push_back((y+1) * (xSegments+1) + x);
			Indices.push_back((y+1) * (xSegments+1) + x + 1);
		}
	}
    
	Finalize();
}

void Plane::draw(glm::vec3 pos, glm::vec4 rot, MODE mode, Shader* shader, Texture* textures, int tex1, int tex2, float opacity, glm::vec4 color)
{
    int planeSize = (Positions.size() + UV.size() + Normals.size()) * sizeof(float);
    if (mode == MODE_TEX2)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures->id[tex1]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures->id[tex2]);
        shader->setBool("drawTex2", true);
        shader->setFloat("opacity", opacity);
    }
    else if (mode == MODE_TEX1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures->id[tex1]);
        shader->setBool("drawTex1", true);
    }
    else if (mode == MODE_COLOR)
    {
        shader->setBool("color", true);
        shader->setVec4("ourColor", color);
    }

    glBindVertexArray(m_VAO);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    float angle = rot.w;
    glm::vec3 rotate = glm::vec3(rot.x, rot.y, rot.z);
    model = glm::rotate(model, glm::radians(angle), rotate);
    shader->setMat4("model", model);
    glDrawElements(GL_TRIANGLES, planeSize, GL_UNSIGNED_INT, 0);

    if (mode == MODE_TEX2) { shader->setBool("drawTex2", false); }
    else if (mode == MODE_TEX1) { shader->setBool("drawTex1", false); }
    else if (mode == MODE_COLOR) { shader->setBool("color", false); }

    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
}