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
	//std::cout << "Position: [x:" << this->worldPosition.x << ", y:" << this->worldPosition.y << ", z:" << this->worldPosition.z << "]" << std::endl;
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw(shader, worldPosition, scale);
	}
}