#pragma once
#include <chrono>
#include <iostream>

class PhyxObj2D {
public:

	//Phyx
	void Update();
	void InitTime();

	//GettersSetters
	double const X(){return x;}
	void X(double _x){x=_x;}
	double const Y(){return y;}
	void Y(double _y){y=_y;}

	double const XV(){return xv;}
	void XV(double _xv){xv=_xv;}
	double const YV(){return yv;}
	void YV(double _yv){yv=_yv;}

	std::chrono::time_point<std::chrono::steady_clock> t;
private:
	double x,y; //position
	double xv,yv; //velocity

};