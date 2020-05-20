#pragma once
//#include "ENG/includes/IrrKlang/irrKlang.h"
#include <ENG/objects/sound.h>
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"
#include <chrono>

#include "gameobj.h"
#include "kldr.h"



class PhyxObj2D : virtual public GameObj
{
public:

	//PhyxObj2D()=default;
	//Phyx
	//void Update();
	void Update(double);
	void Init();
	void ResetA();
	void AddForce(glm::dvec2);
	//void AddForce(double x, double y);

	//GettersSetters
	//*/
//	glm::vec2		Position()	{return glm::vec2(worldPosition.x,worldPosition.z);}
	float const 	X()			{ return worldPosition.x; }
	void			X(float x)	{ worldPosition.x = x; }
	float const 	Y()			{ return worldPosition.z; }
	void			Y(float y)	{ worldPosition.z = y; }

	glm::dvec2		V(){return v;}
	float const 	XV()		{return v.x;}
	void 			XV(float _xv){v.x=_xv;}
	float const 	YV()		{return v.y;}
	void 			YV(float _yv){v.y=_yv;}
	float 			Speed() {return glm::length(v);}

	glm::dvec2		A(){return a;}
	float const 	XA()		{return a.x;}
	void 			XA(float _xa){a.x=_xa;}
	float const 	YA()		{return a.y;}
	void 			YA(float _ya){a.y=_ya;}


	float const 	Mass()		{return mass;}
	void 			Mass(float _m){mass=_m;}
	//*/


	PhyxObj2D* orbiting;
	CircleCollider collider;
	glm::dvec2 pos2D;
	glm::dvec2 v;
	glm::dvec2 a;
	//double xv,yv; //velocity
	//double xa,ya; //acceleration
	//std::chrono::time_point
	//	<std::chrono::steady_clock> t;

	double mass;

	bool actif;
//private:

};


class PhyxENG {
public:
	//void setGamePtr(/*ptr to gameObjects*/);
	PhyxENG(){t = std::chrono::steady_clock::now();}

	void Init(std::vector<GameObj*>*,SoundENG*,CollisionENG *);
	void Update();

//Physics Collisions
	void ReadCollisionMessages();
	void StaticResolution();
	void DynamicResolution();

	//built in functions
 	static glm::vec3 Gravity();//Gravity3D()
 	static glm::vec2 Gravity2D(PhyxObj2D,PhyxObj2D);

 	static glm::vec3 Drag();
 	static glm::vec2 Drag2D();



//private:
 	//std::vector<CollisionPairs> collisions;
 	SoundENG * soundENG;
 	std::vector<PhyxObj2D *> managed;
	std::chrono::time_point
		<std::chrono::steady_clock> t;	
	
	void Collision();
	void Physics();
};