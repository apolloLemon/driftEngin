#pragma once
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"
#include "gameobj.h"
/**
Single Colliders
**/
class Collider : public GameObj {
public:
	int layer;
	Collider()=default;
	Collider(GameObj *,int);
//	void Move(glm::dvec2 delta); //if has parent moves parent//move to gameObj
};
/*
class Collider2D : public Collider {
public:
	void Dim(double x){dim=x;}
	double dim; //dimention0 or radius
};*/

class CircleCollider : public Collider {
public:
	double Dim(){return this->scale.x;}
	void Dim(double s){this->scale = glm::dvec3(s);}
	CircleCollider(GameObj* a,int l): Collider(a,l){}
};

class CollisionObj : virtual public GameObj {
public:
	std::vector<Collider *> collidersLayer(int);
	void CreateCollider(glm::dvec3,int);
//private:
	std::vector<Collider *> colliders;
};

using CollPair = std::pair<GameObj*,Collider*>;
class CollisionMsg {
public:
	CollisionMsg(CollPair,CollPair,int);

	int life; //in frames
	int layer;
	CollPair P;
	CollPair Q;
};

class CollisionENG {
public:
	int LAYERS = 1;
	std::vector<CollisionObj *> managed;
	std::vector<CollisionMsg *> events;

	void Init(std::vector<GameObj*>*);
	void Update();
	std::vector<CollisionMsg *> EventsOf(GameObj *);
	CollisionMsg * CollisionBetween(GameObj *, GameObj *,int);
//private:
	void CheckCollisions();//Generate Events //in update
	void CleanEvents(); //in update

	CollisionMsg * Collision(CollisionObj*, CollisionObj*,int); //used in CheckCollisions to fill events

	bool Collision(CircleCollider*,CircleCollider*);
	//add more for specific collider types
	bool Collision(Collider*,Collider*); //last check for collidertypes

};