#ifndef PHYX_OBJ_H
#define PHYX_OBJ_H

#include "includes/glm/glm.hpp"
#include "includes/glm/ext.hpp"
#include <chrono>

#include "gameObj.h"




class PhyxObj2D : virtual public GameObj
{
public:

	PhyxObj2D();
	//Phyx
	void Update();
	//void Update(/*but with global time*/);
	void InitTime();
	void ResetA();

	void AddForce(double x, double y);

	//GettersSetters
	//*/
	double const 	X()			{ return worldPosition.x; }
	void			X(double x)	{ worldPosition.x = x; }

	double const 	Y()			{ return worldPosition.z; }
	void			Y(double y)	{ worldPosition.z = y; }

	double const 	XV()		{return v.x;}
	void 			XV(double _xv){v.x=_xv;}
	double const 	YV()		{return v.y;}
	void 			YV(double _yv){v.y=_yv;}

	double const 	XA()		{return a.x;}
	void 			XA(double _xa){a.x=_xa;}
	double const 	YA()		{return a.y;}
	void 			YA(double _ya){a.y=_ya;}

	double const V() {return v.length;}
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