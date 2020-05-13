#ifndef RENDER_OBJ_H
#define RENDER_OBJ_H

#include "game.h"
#include <vector>

#include "ENG/model/model.h"
#include "ENG/mesh/mesh.h"
#include "ENG/shaders/shader.h"

/*
enum of RenderObj States
*/

class RenderObj : public virtual GameObj
{
public:
	std::vector<Mesh> meshes;
	Model model;

	void loadModel(std::string path);
	void Draw(Shader* shader);
};


class RenderENG /*: GameENG */{};
#endif