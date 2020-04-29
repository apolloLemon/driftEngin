#include "cube.h"

Cube::Cube()
{
	Positions = std::vector<glm::vec3> {
		// position coords
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),

        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),

        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),

        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),

        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),

        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f)
    };
    UV = std::vector<glm::vec2> {
    	glm::vec2(0.0f, 0.0f),
    	glm::vec2(1.0f, 0.0f),
    	glm::vec2(1.0f, 1.0f),
    	glm::vec2(1.0f, 1.0f),
    	glm::vec2(0.0f, 1.0f),
    	glm::vec2(0.0f, 0.0f),

    	glm::vec2(0.0f, 0.0f),
    	glm::vec2(1.0f, 0.0f),
    	glm::vec2(1.0f, 1.0f),
    	glm::vec2(1.0f, 1.0f),
    	glm::vec2(0.0f, 1.0f),
    	glm::vec2(0.0f, 0.0f),

    	glm::vec2(1.0f, 0.0f),
    	glm::vec2(1.0f, 1.0f),
    	glm::vec2(0.0f, 1.0f),
    	glm::vec2(0.0f, 1.0f),
    	glm::vec2(0.0f, 0.0f),
    	glm::vec2(1.0f, 0.0f),

    	glm::vec2(1.0f, 0.0f),
    	glm::vec2(1.0f, 1.0f),
    	glm::vec2(0.0f, 1.0f),
    	glm::vec2(0.0f, 1.0f),
    	glm::vec2(0.0f, 0.0f),
    	glm::vec2(1.0f, 0.0f),

    	glm::vec2(0.0f, 1.0f),
    	glm::vec2(1.0f, 1.0f),
    	glm::vec2(1.0f, 0.0f),
    	glm::vec2(1.0f, 0.0f),
    	glm::vec2(0.0f, 0.0f),
    	glm::vec2(0.0f, 1.0f),

    	glm::vec2(0.0f, 1.0f),
    	glm::vec2(1.0f, 1.0f),
    	glm::vec2(1.0f, 0.0f),
    	glm::vec2(1.0f, 0.0f),
    	glm::vec2(0.0f, 0.0f),
    	glm::vec2(0.0f, 1.0f)
    };
    Normals = std::vector<glm::vec3> {
    	glm::vec3( 0.0f,  0.0f, -1.0f),
    	glm::vec3( 0.0f,  0.0f, -1.0f),
    	glm::vec3( 0.0f,  0.0f, -1.0f),
    	glm::vec3( 0.0f,  0.0f, -1.0f),
    	glm::vec3( 0.0f,  0.0f, -1.0f),
    	glm::vec3( 0.0f,  0.0f, -1.0f),

    	glm::vec3( 0.0f,  0.0f,  1.0f),
    	glm::vec3( 0.0f,  0.0f,  1.0f),
    	glm::vec3( 0.0f,  0.0f,  1.0f),
    	glm::vec3( 0.0f,  0.0f,  1.0f),
    	glm::vec3( 0.0f,  0.0f,  1.0f),
    	glm::vec3( 0.0f,  0.0f,  1.0f),

    	glm::vec3(-1.0f,  0.0f,  0.0f),
    	glm::vec3(-1.0f,  0.0f,  0.0f),
    	glm::vec3(-1.0f,  0.0f,  0.0f),
    	glm::vec3(-1.0f,  0.0f,  0.0f),
    	glm::vec3(-1.0f,  0.0f,  0.0f),
    	glm::vec3(-1.0f,  0.0f,  0.0f),

    	glm::vec3( 1.0f,  0.0f,  0.0f),
    	glm::vec3( 1.0f,  0.0f,  0.0f),
    	glm::vec3( 1.0f,  0.0f,  0.0f),
    	glm::vec3( 1.0f,  0.0f,  0.0f),
    	glm::vec3( 1.0f,  0.0f,  0.0f),
    	glm::vec3( 1.0f,  0.0f,  0.0f),

    	glm::vec3( 0.0f, -1.0f,  0.0f),
    	glm::vec3( 0.0f, -1.0f,  0.0f),
    	glm::vec3( 0.0f, -1.0f,  0.0f),
    	glm::vec3( 0.0f, -1.0f,  0.0f),
    	glm::vec3( 0.0f, -1.0f,  0.0f),
    	glm::vec3( 0.0f, -1.0f,  0.0f),

    	glm::vec3( 0.0f,  1.0f,  0.0f),
    	glm::vec3( 0.0f,  1.0f,  0.0f),
    	glm::vec3( 0.0f,  1.0f,  0.0f),
    	glm::vec3( 0.0f,  1.0f,  0.0f),
    	glm::vec3( 0.0f,  1.0f,  0.0f),
    	glm::vec3( 0.0f,  1.0f,  0.0f)
    };

    Finalize();
}

void Cube::draw(glm::vec3 pos, glm::vec4 rot, MODE mode, Shader* shader, Texture* textures, int tex1, int tex2, float opacity, glm::vec4 color)
{
    int cubeSize = Positions.size();
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
    glDrawArrays(GL_TRIANGLES, 0, cubeSize);

    if (mode == MODE_TEX2) { shader->setBool("drawTex2", false); }
    else if (mode == MODE_TEX1) { shader->setBool("drawTex1", false); }
    else if (mode == MODE_COLOR) { shader->setBool("color", false); }

    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
}