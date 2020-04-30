#include "perlin.h"
#include <cmath>
#include <vector>
#include <random>
/*
function IntNoise(32-bit integer: x)			 
	x = (x<<13) ^ x;
	return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 7fffffff) / 1073741824.0);    	
	//return ( 1.0 - ( (x * (x * x * prime5 + prime6) + prime10) & 7fffffff) / 1073741824.0);
end IntNoise function
*/

double rayon (double x, double y){
	return pow(pow(x,2)+pow(y,2),.5);
}


float PerlinNoise1D::Get(uint32_t x) {
	//x = std::pow((x<<13),x);
	//return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
	std::srand(x);
	return (std::rand()%100000)/100000.0;
}