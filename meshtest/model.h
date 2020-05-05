#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#include "shaders/shader.h"
#include "meshtest/mesh.h"

class Model
{
public:
	// model data
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;

	// constructor, expects a filepath to a 3D model.
	Model(std::string const &path);

	// draws the model, and thus all its meshes
	void Draw(Shader* shader);

private:
	// model data

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif