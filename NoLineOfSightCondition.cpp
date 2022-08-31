#include "NoLineOfSightCondition.h"

bool NoLineOfSightCondition::IsTrue(Agent* agent, float deltaTime)
{
	for (Agent* t : m_children)
	{
		if (agent->GetNavMesh()->LineIntersectsObstacle(agent->GetPosition(), t->GetPosition()))
		{
			std::cout << "Lost Sight on targets" << std::endl;
			return true;
		}
	}
	return false;
}
