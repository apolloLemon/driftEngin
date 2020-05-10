#ifndef RENDER_OBJ_H
#define RENDER_OBJ_H

#include "gameObj.h"

#include <vector>

#include "model/model.h"
#include "mesh/mesh.h"
#include "shaders/shader.h"

/*
enum of RenderObj States
*/

class RenderObj : public virtual GameObj
{
public:
	std::vector<Mesh*> meshes;
	Model model;

	void loadModel(std::string path);
	void Draw(Shader* shader);
};


class RenderENG /*: GameENG */{};
#endif