#include "kldr.h"
//static const int LAYERS = 1;

Collider::Collider(GameObj* p,int l){
	parent=p;
	layer=l;
	scale = glm::vec3(1);
}

std::vector<Collider *> CollisionObj::collidersLayer(int l){
	std::vector<Collider *> out;
	for(auto& c : colliders) if(c->layer==l) out.push_back(c);
	return out;
}
void CollisionObj::CreateCollider(glm::dvec3 pos,int l){
	Collider *in = new CircleCollider(this,l);
	in->position = pos;
	colliders.push_back(in);
}

void CollisionObj::CreateCollider(glm::dvec3 pos,int l, float size){
	Collider *in = new CircleCollider(this,l, size);
	in->position = pos;
	colliders.push_back(in);
}

void CollisionENG::Init(std::vector<GameObj*>* gameobjects){
	managed.clear();
	for (unsigned int i = 0; i < gameobjects->size(); i++)
	{
		GameObj* go = gameobjects->at(i);
		CollisionObj* cast = dynamic_cast<CollisionObj *>(go);
		if(cast) managed.push_back(cast);
	}
}

void CollisionENG::Update(){
//	TESTLOG("0 Update");
	CheckCollisions();//Generate Events //in update
	CleanEvents();
}

void CollisionENG::CheckCollisions(){
//	TESTLOG("1 CheckCollisions");
	for(int i=0;i<managed.size();i++){
			CollisionObj * p = managed[i];
		for(int j=i+1;j<managed.size();j++){ //this kind of loop allows us to only check a couple once
			for(int l=0;l<LAYERS;l++){
				CollisionObj * q = managed[j];
				CollisionMsg * coll = Collision(p,q,l);
				if(coll) events.push_back(coll);
			}
		}
	}
}

void CollisionENG::CleanEvents(){
//	TESTLOG("2 CleanEvents");
	for(auto& e : events)
		if(e->life<=0){
			delete e;
			e=nullptr;
		} else e->life--;
					
	events.erase(
		std::remove(events.begin(), events.end(), nullptr),
		events.end()
		);
}

CollisionMsg * CollisionENG::Collision(CollisionObj* p,CollisionObj* q,int l){
//	TESTLOG("11 Collision" TAB p->name TAB q->name TAB l);
	std::vector<Collider *> pcs = p->collidersLayer(l);
	std::vector<Collider *> qcs = q->collidersLayer(l);
//	TESTLOG("P collider num:" TAB pcs.size());
	int tests = 0;
	for(auto& pc : pcs) 
		for(auto& qc : qcs){
			tests++;
			if(ColliderCollision(pc,qc)){
				TESTLOG("12 Collision Detected" TAB p->name TAB q->name TAB l);
				return new CollisionMsg(std::make_pair(p,pc),std::make_pair(q,qc),l);
			}
		} 
//	TESTLOG("Collision Tests:" TAB tests);
	return nullptr;
}

CollisionMsg * CollisionENG::CollisionBetween(GameObj* p,GameObj* q,int l){
	for(auto& e : events)
		if((e->P.first==p)&&(e->Q.first==q)&&(e->layer==l))
			return e;
	return nullptr;
}

bool CollisionENG::ColliderCollision(Collider * A,Collider * B){
//	TESTLOG("111 Collider Collision");
	CircleCollider *Ac = dynamic_cast<CircleCollider *>(A);
	CircleCollider *Bc = dynamic_cast<CircleCollider *>(B);
	if(Ac&&Bc) {
		//TESTLOG("112 CircleCollider Collision Type Detected");
		return CircleCollision(Ac,Bc);}
	return false;
}

bool CollisionENG::CircleCollision(CircleCollider * A,CircleCollider * B){
	return (glm::distance(A->worldPosition(),B->worldPosition()) <= (A->Dim()+B->Dim())); 
}

CollisionMsg::CollisionMsg(CollPair p, CollPair q, int l)
: P(p), Q(q), layer(l), life(1) {}

/*
CollisionMsg CircleCollider::collision(CircleCollider g){
	CollisionMsg out;
	out.nor = glm::normalize(g.pos-pos);
	out.tan = glm::vec2(out.nor.y*-1.,out.nor.x);
	out.overlap = (dim+g.dim)-glm::distance(pos,g.pos);
	return out;
}*/
/*
bool CircleCollider::isin(CircleCollider g){
	return (glm::distance(pos,g.pos) <= (dim+g.dim));
}

bool CircleCollider::isin(glm::dvec2 other){
	return (
		glm::distance(this->pos,other)
		<= this->dim);
}
*/
/*bool SphereCollider::boolin(glm::vec3 other){
	return (
		glm::distance(transform.pos,other)
		<= dim);
}*/
