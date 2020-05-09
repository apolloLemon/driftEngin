#include "renderObj.h"

void RenderObj::loadModel(std::string path)
{
	model.loadModel(path);
	for (unsigned int i = 0; i < model.meshes.size(); i++)
	{
		this->meshes.push_back(&model.meshes[i]);
	}
}

void RenderObj::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw(shader, this->worldPosition, this->scale);
	}
}