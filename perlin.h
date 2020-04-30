class PerlinNoise {
public:
	PerlinNoise(unsigned int _seed): seed(_seed) {}
	double Get() {return seed}



private:
	unsigned int seed;
};


/*
class SphereNoise : public PerlinNoise {

};
*/