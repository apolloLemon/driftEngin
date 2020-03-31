#include <iostream>
#include <thread>
#include <chrono>

#include "phyx.h"

using namespace std::literals::chrono_literals; //for sleep_for(0.01s)
int main(){
	
	PhyxObj2D p; //point
	p.X(0);p.Y(0); //start pos
	p.XV(5);p.YV(5); //start velocity
	p.InitTime();

	while(1){
		std::cout	<<"x: "<<p.X()
					<<", y: "<<p.Y()
					<<std::endl;

		p.Update();
		std::this_thread::sleep_for(0.01s);
	}

	return 0;
}