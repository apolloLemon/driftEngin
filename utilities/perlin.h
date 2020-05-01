/*
PerlinNoise
	m-dimentional noise function


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
	float Noise(int x);
};

class Perlin2D : public PerlinNoise {
public:
	float Noise(int x, int y);
};

class Perlin3D : public PerlinNoise {
public:
	float Noise(int x, int y, int z);
};
/*
*/