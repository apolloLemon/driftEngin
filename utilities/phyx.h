#pragma once
#include <chrono>
#include <cmath>
#include <iostream>

#include "../gameobjects/gameObj.h"

class PhyxObj2D : virtual public GameObj {
public:

	//Phyx
	void Update();
	void InitTime();
	void ResetA();

	void AddForce(double x, double y);

	//GettersSetters
	double const X(){return x;}
	//double & X(){return x;}
	void X(double _x){x=_x;}
	double const Y(){return y;}
	//double & Y(){return y;}
	void Y(double _y){y=_y;}

	double const XV(){return xv;}
	void XV(double _xv){xv=_xv;}
	double const YV(){return yv;}
	void YV(double _yv){yv=_yv;}

	double const XA(){return xa;}
	void XA(double _xa){xa=_xa;}
	double const YA(){return ya;}
	void YA(double _ya){ya=_ya;}

	double const V();

private:
	double x,y; //position
	double xv,yv; //velocity
	double xa,ya; //acceleration
	std::chrono::time_point
		<std::chrono::steady_clock> t;

};