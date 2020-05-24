#include "perlin.h"
#include <iostream>

float Perlin3D::gen(int i,int j, int k){
	float xf=1.f/(res-1);
	float yf=1.f/(res-1);
	float zf=1.f/(res-1);

//	for(int i=0;i<res;i++)
//		for(int j=0;j<res;j++)
//			for(int k=0;k<res;k++){
				float x = xf*i;
				float y = yf*j;
				float z = zf*k;
				float sum=0;
				float freq =1.12;
				float scale = b;

				for(int oct =0;oct<4;oct++){
					glm::vec3 p(x*freq,y*freq,z*freq);
					//glm::vec3 p(x,y,z);
					float val = glm::perlin(p)/scale;
					sum+=val;
					freq*=2.f;
					scale*=b;
				}
//				float result = (sum+1.f)/2.f;
				//noise[i][j][k] = (sum+1.f)/2.f;
				return (sum+1.f)/2.f;
			//}
}