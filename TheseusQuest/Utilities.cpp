#include <random>
#include <time.h>
#include "Utilities.h"

float Utilities::Random(float min, float max)
{
	return min + (max - min) * (float)rand() / (float)RAND_MAX;
}

Vector2 Utilities::ConvertVector(glm::vec2 vec)
{
	return Vector2{ vec.x, vec.y };
}