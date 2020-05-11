#pragma once

#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"

#include "game.h"

/*
enum of CollisionObj States?
*/

struct CollisionMsg {
	//vectors representing collision
	// vec : obj1 - obj2
	// tangents, etc..
	// overlap amount
};
/*struct CollisionTransform2D {
	glm::vec2 pos;
	//rot
	//scale
};*/

class CollisionObj {};

class CollisionObj2D {
public:
	//virtual CollisionMsg * collision(CollisionObj); //null if no collision, ptr
	bool collision(CollisionObj2D);
//private:

	glm::vec2 pos;
	float dim; //dimention0 or radius
};


class CollisionENG /*?: GameENG ?*/ {};



//particular colliders
class CircleCollider : public CollisionObj2D {
public:
//private:
	bool boolin(glm::vec2);

};
/*class SphereCollider : public CollisionObj {
public:
	bool boolin(glm::vec3);	
};*/

//class BoxCollider2D : public CollisionObj {};
//class BoxCollider3D : public CollisionObj {};

