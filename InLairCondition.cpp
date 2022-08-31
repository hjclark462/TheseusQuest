#include "InLairCondition.h"

bool InLairCondition::IsTrue(Agent* agent, float deltaTime)
{
	return (CheckCollisionPointRec({ agent->GetPosition().x, agent->GetPosition().y }, agent->GetNavMesh()->GetLair()));
}
