#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <vector>
#include <string>
#include <iostream>

#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/gtc/matrix_transform.hpp"
#if 1
	#include <iostream>
	#define TAB <<"\t"<<
	#define TESTLOG(X) std::cout << X << std::endl
#else
	#define TAB 
	#define TESTLOG(X)
#endif

class GameObj
{
public:
	std::vector<GameObj*> children;
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
	glm::vec3 worldPositionf(){
		glm::vec3 out = position;
		if(parent) out += parent->worldPositionf();
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
	void Move(glm::vec3 delta){
		if(parent) parent->Move(delta);
		else position += delta;
	}
	void MoveTo(glm::vec3 pos){
		if(parent) parent->MoveTo(pos);
		else position = pos;
	}
	void MoveTo(glm::dvec2 pos){
		if(parent) parent->MoveTo(pos);
		else position = glm::dvec3(pos.x,0,pos.y);
	}

	glm::dvec3 worldRotation(){
		glm::dvec3 out = rotation;
		if(parent) out += parent->rotation; //this is probably wrongs
		return out;
	};

	void attach(GameObj* go, glm::vec3 offset = glm::vec3(0.0f));
//	glm::dvec3 worldScale();//should this be relative :?

	// constructors
	GameObj(); // default
	GameObj(glm::vec3 wPos, glm::vec3 scale);
	virtual ~GameObj()=default;
};

#endif