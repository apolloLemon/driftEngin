#pragma once

#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"

#include "game.h"

/*
enum of CollisionObj States?
*/

struct kldrMsg {};
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
};


class KldrENG /*?: GameENG ?*/ {};



//particular colliders
class BoundryCollider : public KldrObj {
	float radius;
};
class CircleCollider : public BoundryCollider {
public:
	bool boolin(glm::vec2);

};
//class SphereCollider : public BoundryCollider {};

//class BoxCollider2D : public KldrObj {};
//class BoxCollider3D : public KldrObj {};

