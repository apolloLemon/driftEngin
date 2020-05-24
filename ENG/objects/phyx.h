#pragma once
//#include "ENG/includes/IrrKlang/irrKlang.h"
#include <ENG/objects/sound.h>
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"
#include <chrono>

#include "gameobj.h"
#include "kldr.h"
class PhyxObj2D : virtual public GameObj, public CollisionObj
{
public:

	//PhyxObj2D()=default;
	//Phyx
	//void Update();
	void Update(double);
//	void Init();
	void ResetV();
	void ResetA();
	void AddForce(glm::dvec2);
	//void AddForce(double x, double y);

	//GettersSetters
	//*/
//	glm::vec2		Position()	{return glm::vec2(worldPosition.x,worldPosition.z);}
	float const 	X()			{ return worldPosition().x; }
//	void			X(float x)	{ Move(glm::vec2(x,0)); }
	float const 	Y()			{ return worldPosition().z; }
//	void			Y(float y)	{ worldPosition().z = y; }

	glm::dvec2		V();
	void			V(glm::dvec2 _v);
	void			dV(glm::dvec2 _v);
	float const 	XV();
	void 			XV(float _xv);
	float const 	YV();
	void 			YV(float _yv);
	float 			Speed();

	glm::dvec2		A(){return a;}
	float const 	XA()		{return a.x;}
	void 			XA(float _xa){a.x=_xa;}
	float const 	YA()		{return a.y;}
	void 			YA(float _ya){a.y=_ya;}


	float const 	Mass()		{return mass;}
	void 			Mass(double _m){mass=_m;}
	//*/

	bool const 		isKinematic() {return kinematic;}
	void 	 		isKinematic(bool b) {kinematic=b;}

	bool Orbiting(PhyxObj2D* other){
		for(auto po : orbiting) if(po==other) return true;
		return false;
	}

	std::vector<PhyxObj2D*> orbiting;

//	glm::dvec2 pos2D; //now directly use gameObejct stuff
	glm::dvec2 v;
	glm::dvec2 a;
	//double xv,yv; //velocity
	//double xa,ya; //acceleration
	//std::chrono::time_point
	//	<std::chrono::steady_clock> t;

	double mass;

	bool actif;
	bool kinematic=false;
//private:

};

enum GravityMode {
	Everything,
	Orbiting,
	Directional,
	None
};


class PhyxENG {
public:
	//void setGamePtr(/*ptr to gameObjects*/);
	PhyxENG(){t = std::chrono::steady_clock::now();}

	void Init(std::vector<GameObj*>*,CollisionENG *,SoundENG*);
	void Update();

//Physics Collisions
	void StaticResolution(Collider *, Collider *);
	void StaticResolution(PhyxObj2D*, Collider *,PhyxObj2D*, Collider *); //uses weight in resolution and checks for kinematics
	void DynamicResolution(PhyxObj2D*, Collider *,PhyxObj2D*, Collider *);

	//built in functions
// 	glm::vec3 Gravity();//Gravity3D()
 	glm::dvec2 Gravity2D(PhyxObj2D *,PhyxObj2D*);

// 	glm::vec3 Drag();
// 	glm::vec2 Drag2D();



//private:
 	//std::vector<CollisionPairs> collisions;
 	SoundENG * soundENG;
 	CollisionENG * collisionENG;
 	std::vector<PhyxObj2D *> managed;
	std::chrono::time_point
		<std::chrono::steady_clock> t;	
	int PHYX_LAYER=0;
	bool clipping=true;
	double timescale=1;
	float G = 1.0E-5;
	GravityMode gravitymode = Everything;
	double colEl = .9; //collisionElasticity
	double fps=0; int framecounter=0; double timecounter=0;

//	void Collision();
//	void Physics();
};