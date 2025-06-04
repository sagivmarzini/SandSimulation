#include "Random.h"

void Random::seed(unsigned int value)
{
	gen.seed(value);
}

int Random::intInRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

float Random::floatInRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}