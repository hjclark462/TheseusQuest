#pragma once
#include <glm/glm.hpp>
#include "raylib.h"

class Utilities
{
public:
	static float Random(float min, float max);
	static Vector2 ConvertVector(glm::vec2 vec);
};

