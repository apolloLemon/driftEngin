#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
	// constructor
	Model(char* path);

	void Draw(Shader* shader);

private:
	// model data
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
}

#endif