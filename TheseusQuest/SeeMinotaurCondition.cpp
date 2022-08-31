#include "SeeMinotaurCondition.h"

bool SeeMinotaurCondition::IsTrue(Agent* agent, float deltaTime)
{
	return(!agent->GetNavMesh()->LineIntersectsObstacle(agent->GetPosition(), agent->GetTarget()->GetPosition()));
}
