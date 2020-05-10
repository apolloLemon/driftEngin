#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <limits>

#include "shaders/shader.h"
#include "mesh/mesh.h"
#include "objects/game.h"

class Model
{
public:
	// model data
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;

	// constructor
	Model();

	void loadModel(std::string path);

private:
	// model data
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	Material loadMaterial(aiMaterial* mat);
};

#endif