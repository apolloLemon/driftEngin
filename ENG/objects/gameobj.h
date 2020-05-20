#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <vector>
#include <string>

#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/gtc/matrix_transform.hpp"

/*
enum of GameObj States
*/

class GameObj
{
public:
	GameObj * parent;

	std::string name;
	// Transformation variables
	glm::dvec3 position;
	glm::dvec3 scale;
	glm::dvec3 rotation; // Picth / Yaw / Roll

	glm::dvec3 worldPosition(){
		glm::dvec3 out = position;
		if(parent) out += parent->worldPosition();
		return out;
	};
	glm::dvec2 worldPosition2D(){
		glm::dvec2 out = glm::dvec2(position.x,position.z);
		if(parent) out += parent->worldPosition2D();
		return out;
	};
	void Move(glm::dvec2 delta){
		if(parent) parent->Move(delta);
		else position += glm::dvec3(delta.x,0,delta.y);
	}
	void Move(glm::dvec3 delta){
		if(parent) parent->Move(delta);
		else position += delta;
	}

	glm::dvec3 worldRotation(){
		glm::dvec3 out = rotation;
		if(parent) out += parent->rotation; //this is probably wrongs
		return out;
	};
//	glm::dvec3 worldScale();//should this be relative :?

	// constructors
	GameObj(); // default
	GameObj(glm::vec3 wPos, glm::vec3 scale);
	virtual ~GameObj()=default;
};

#endif