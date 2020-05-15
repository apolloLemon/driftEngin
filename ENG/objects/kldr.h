#pragma once
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"
/*
enum of CollisionObj States?
*/
/*struct CollisionTransform2D {
	glm::vec2 pos;
	//rot
	//scale
};*/

class CollisionObj {};

class CollisionObj2D {
public:
	//virtual CollisionMsg * collision(CollisionObj); //null if no collision, ptr
	//virtual bool collision(CollisionObj2D)=0;
//private:

	void Dim(double x){dim=x;}
	void Pos(glm::dvec2 x){pos=x;}

	glm::dvec2 pos;
	double dim; //dimention0 or radius
};

//particular colliders
class CircleCollider : public CollisionObj2D {
public:
	//CollisionMsg collision(CircleCollider) /*override*/;
//private:
	bool isin(CircleCollider);
	bool isin(glm::dvec2);

};
/*class SphereCollider : public CollisionObj {
public:
	bool boolin(glm::vec3);	
};*/

//class BoxCollider2D : public CollisionObj {};
//class BoxCollider3D : public CollisionObj {};