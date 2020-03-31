#include <iostream>
#include <thread>
#include <chrono>

#include "phyx.h"

using namespace std::literals::chrono_literals; //for sleep_for(0.01s)
int main(){
	
	PhyxObj2D p; //point
	p.X(0);p.Y(300); //start pos
	p.XV(0);p.YV(0); //start velocity u/s
	p.XA(0);p.YA(-10); //acceleration u2/s
	p.InitTime();

	while(1){
		std::cout	<<"x: "<<p.X()
					<<", y: "<<p.Y()
					<<",\tspeed: "<<p.V()
					<<std::endl;

		p.Update();
		std::this_thread::sleep_for(1s);
	}

	return 0;
}