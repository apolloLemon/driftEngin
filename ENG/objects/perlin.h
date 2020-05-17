#pragma once
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/ext.hpp"
#include "ENG/includes/glm/gtc/noise.hpp"
#include <iostream>
#include <array>
const int res = 100;
const float a = 1.12;
const float b = 2;
class Perlin3D {
public:
	std::array<std::array<std::array<float,res>,res>,res> noise;

	float gen(int,int,int);

	int n(float a){
		int out = (int)((a+1.f)*res/2);
		if(out==100) out--;
		return out;
	}

	float get(glm::vec3 v){
		float a = gen(n(v.x),n(v.y),n(v.z));
		//std::cout << n(v.x)<<","<<n(v.y)<<","<<n(v.z)<<": \t"<<a<<std::endl;
		return a;
	}
};