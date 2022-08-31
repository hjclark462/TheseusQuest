#include "LeaveCondition.h"

bool LeaveCondition::IsTrue(Agent* agent, float deltaTime)
{
	return CheckCollisionPointRec({ agent->GetPosition().x,agent->GetPosition().y }, agent->GetNavMesh()->GetExit());
}
