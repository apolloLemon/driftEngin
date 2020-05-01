#include "perlin.h"
#include <iostream>

int main(){

	Perlin3D a;

	int I=30,J=120;

	for(int i=0;i<I;i++){
		for(int j=0;j<J;j++){
			float r = a.Noise(i,j,0);
			if (r>0.9) 
				std::cout << "8";
			else if ((r<=0.75) && (r>0.5)) 
				std::cout << "3";
			else if ((r<=0.9) && (r>0.75)) 
				std::cout << "0";
			else std::cout << " ";
		}
		
		std::cout<<std::endl;
	}


	return 0;
}