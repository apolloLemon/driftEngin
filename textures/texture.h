#ifndef TEXTURE_H
#define TEXTURE_H

#include "includes/glad/glad.h"
#include <GLFW/glfw3.h>

#include "includes/stb_image/stb_image.h"
#include <vector>
#include <string>
#include <iostream>

class Texture
{
public:
	Texture(std::string path);

	void add(	std::string name,
				GLenum format	= GL_RGB,
				GLint sParam 	= GL_REPEAT,
				GLint tParam 	= GL_REPEAT,
				GLint minParam	= GL_LINEAR,
				GLint magParam	= GL_LINEAR );

	std::vector<unsigned int> id;
	std::string texPath;
};

#endif