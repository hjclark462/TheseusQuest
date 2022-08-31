#include "BraveryCondition.h"

bool BraveryCondition::IsTrue(Agent* agent, float deltaTime)
{
	if (agent->GetBravery() <= 0)
	{
		return true;
	}
	return false;
}
