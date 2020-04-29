#include "texture.h"

Texture::Texture(std::string path) : texPath(path)
{

}

void Texture::add(std::string name, GLenum format, GLint sParam, GLint tParam, GLint minParam, GLint magParam)
{
	unsigned int tex;

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magParam);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data;
    if (format == GL_RGB)
        data = stbi_load((texPath+name).c_str(), &width, &height, &nrChannels, 0);
    else
        data = stbi_load((texPath+name).c_str(), &width, &height, &nrChannels, 4);
    if (data)
    {
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    	glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
    	std::cout << "Failed to load texture." << std::endl;
    	std::cout << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);

    id.push_back(tex);
}