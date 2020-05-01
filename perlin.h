/*
GOAL:
	make spherical noise map

	get circleMesh vector3
	mutl circleMesh by spherical noise map
*/

//Noise Object
#include <cstdint>
class PerlinNoise {
public:
};


class Perlin1D : public PerlinNoise {
public:
	float Rand(int x);
};

class Perlin2D : public PerlinNoise {
public:
	float Rand(int x, int y);
};
/*
*/