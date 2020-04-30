#include "perlin.h"
#include <iostream>

int main(){

	PerlinNoise1D a(1);

	for(int i=0;i<100;i++)
		std::cout << a.Get(i) << ((!(i%4))?"\n":",");


	std::cout << a.Get(10000000) <<std::endl;
	std::cout << a.Get(10001000) <<std::endl;
	std::cout << a.Get(10002000) <<std::endl;

	std::cout << a.Get(-1) <<std::endl;

	return 0;
}