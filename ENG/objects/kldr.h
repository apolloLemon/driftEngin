#pragma once

#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"

#include "game.h"

/*
enum of CollisionObj States?
*/

struct kldrMsg {
	//vectors representing collision
	// vec : obj1 - obj2
	// tangents, etc..
	// overlap amount
};
struct kldrTransform2D {
	glm::vec2 pos;
	//rot
	//scale
};

class KldrObj : public virtual GameObj
{
public:
	virtual KldrMsg * collision(KldrObj); //null if no collision, ptr 
//private:

	kldrTransform2D transform;

	float dim; //dimention0 or radius
};


class KldrENG /*?: GameENG ?*/ {};



//particular colliders
class CircleCollider : public KldrObj {
public:
	bool boolin(glm::vec2);

};
class SphereCollider : public KldrObj {
public:
	bool boolin(glm::vec3);	
};

//class BoxCollider2D : public KldrObj {};
//class BoxCollider3D : public KldrObj {};

