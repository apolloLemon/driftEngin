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
	PerlinNoise(unsigned int _seed): seed(_seed){}
	virtual float Get(uint32_t x)=0;

private:
	unsigned int seed;
};


class PerlinNoise1D : public PerlinNoise {
public:
	PerlinNoise1D(unsigned int _seed) : PerlinNoise(_seed){}

	float Get(uint32_t x) override;
};
/*
*/