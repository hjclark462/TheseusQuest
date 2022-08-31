#include <random>
#include <time.h>
#include "Utilities.h"

float Utilities::Random(float min, float max)
{
	return min + (max - min) * (float)rand() / (float)RAND_MAX;
}