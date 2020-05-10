#ifndef PHYX_OBJ_H
#define PHYX_OBJ_H

#include "includes/glm/glm.hpp"
#include "includes/glm/ext.hpp"
#include <chrono>

#include "game.h"



class PhyxObj2D : virtual public GameObj
{
public:

	//PhyxObj2D()=default;
	//Phyx
	void Update();
	//void Update(/*but with global time*/);
	void InitTime();
	void ResetA();

	void AddForce(glm::vec2);
	//void AddForce(double x, double y);

	//GettersSetters
	//*/
	float const 	X()			{ return worldPosition.x; }
	void			X(float x)	{ worldPosition.x = x; }

	float const 	Y()			{ return worldPosition.z; }
	void			Y(float y)	{ worldPosition.z = y; }

	float const 	XV()		{return v.x;}
	void 			XV(float _xv){v.x=_xv;}
	float const 	YV()		{return v.y;}
	void 			YV(float _yv){v.y=_yv;}

	float const 	XA()		{return a.x;}
	void 			XA(float _xa){a.x=_xa;}
	float const 	YA()		{return a.y;}
	void 			YA(float _ya){a.y=_ya;}

	float const V() {return v.length();}
	//*/
	glm::vec2 v;
	glm::vec2 a;
	//double xv,yv; //velocity
	//double xa,ya; //acceleration
	std::chrono::time_point
		<std::chrono::steady_clock> t;
//private:

};


class PhyxENG /*?: GameENG ?*/{
public:
	void setGamePtr(/*ptr to gameObjects*/);
 
	//built in functions
 	static glm::vec3 Gravity();//Gravity3D()
 	static glm::vec2 Gravity2D();

 	static glm::vec3 Drag();
 	static glm::vec2 Drag2D();
};
#endif