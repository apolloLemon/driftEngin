#ifndef PHYX_OBJ_H
#define PHYX_OBJ_H

#include "gameObj.h"

#include <chrono>
#include <cmath>
#include <iostream>


class PhyxObj2D : virtual public GameObj
{
public:

	PhyxObj2D();
	//Phyx
	void Update();
	void InitTime();
	void ResetA();

	void AddForce(double x, double y);

	//GettersSetters
	double const 	X()			{ return worldPosition.x; }
	void			X(double x)	{ worldPosition.x = x; }

	double const 	Y()			{ return worldPosition.z; }
	void			Y(double y)	{ worldPosition.z = y; }

	double const 	XV()		{return xv;}
	void 			XV(double _xv){xv=_xv;}
	double const 	YV()		{return yv;}
	void 			YV(double _yv){yv=_yv;}

	double const 	XA()		{return xa;}
	void 			XA(double _xa){xa=_xa;}
	double const 	YA()		{return ya;}
	void 			YA(double _ya){ya=_ya;}

	double const V();

private:
	double xv,yv; //velocity
	double xa,ya; //acceleration
	std::chrono::time_point
		<std::chrono::steady_clock> t;

};


class PhyxENG /*?: GameENG ?*/{
	
	//static function gravity(phyxObj, phyxObj)
	//static function
};
#endif