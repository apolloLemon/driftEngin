#ifndef SHADER_H
#define SHADER_H

#include "ENG/includes/glad/glad.h" // include glad to get all the required OpenGL headers

// glm library
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/gtc/matrix_transform.hpp"
#include "ENG/includes/glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void use();
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	void setVec3(const std::string &name, const glm::vec3 &vec) const;

	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setVec4(const std::string &name, const glm::vec4 &vec) const;

private:
	// utility function for checking shader compilation/linking errors
	// ---------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif