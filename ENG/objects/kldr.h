#pragma once
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"
#include "game.h"
static const int LAYERS = 1;

/**
Single Colliders
**/
class Collider : public GameObj {
public:
	GameObj * parent;
	int layer;
};

class Collider2D : public Collider {
public:
	//virtual CollisionMsg * collision(CollisionObj); //null if no collision, ptr
	//virtual bool collision(Collider2D)=0;
//private:

	void Dim(double x){dim=x;}
	void Pos(glm::dvec2 x){pos=x;}

	glm::dvec2 pos;
	double dim; //dimention0 or radius
};

//particular colliders
class CircleCollider : public Collider2D {
public:
	//CollisionMsg collision(CircleCollider) /*override*/;
//private:
//	bool isin(CircleCollider);
//	bool isin(glm::dvec2);

};

class CollisionObj : virtual public GameObj {
	std::vector<Collider *> colliders;
	std::vector<Collider *> collidersLayer(int);
};

class CollisionMsg {
	int life = 0; //in frames
	std::pair<GameObj*,Collider*> A;
	std::pair<GameObj*,Collider*> B;
};

class CollisionENG {
public:
	std::vector<CollisionObj *> managed;
	std::vector<CollisionMsg> events;

	void Update();
	void CheckCollisions();//Generate Events //in update
	void CleanEvents(); //in update

	CollisionMsg Collision(CollisionObj*, CollisionObj*); //used in CheckCollisions to fill events

	bool Collision(CircleCollider*,CircleCollider*);
	//add more for specific collider types
	bool Collision(Collider*,Collider*); //last check for collidertypes

}