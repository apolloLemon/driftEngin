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
	int layer;

	Collider(GameObj *,int);
	void Move(glm::dvec2 delta); //if has parent moves parent

};

class Collider2D : public Collider {
public:
	void Dim(double x){dim=x;}
	double dim; //dimention0 or radius
};

class CircleCollider : public Collider2D {
public:
};

class CollisionObj : virtual public GameObj {
	std::vector<Collider *> colliders;
	std::vector<Collider *> collidersLayer(int);

	void CreateCollider(glm::dvec3 pos,int l){
		Collider in = new CircleCollider(this,l);
		in.position = pos;
		colliders.push_back(in);
	}
};

class CollisionMsg {
	int life = 1; //in frames
	std::pair<GameObj*,Collider*> A;
	std::pair<GameObj*,Collider*> B;
};

class CollisionENG {
public:
	std::vector<CollisionObj *> managed;
	std::vector<CollisionMsg> events;

	void Update();
	std::vector<CollisionMsg> EventsOf(GameObj *);
//private:
	void CheckCollisions();//Generate Events //in update
	void CleanEvents(); //in update

	CollisionMsg Collision(CollisionObj*, CollisionObj*); //used in CheckCollisions to fill events

	bool Collision(CircleCollider*,CircleCollider*);
	//add more for specific collider types
	bool Collision(Collider*,Collider*); //last check for collidertypes

}