#include "ReturnedCondition.h"

bool ReturnedCondition::IsTrue(Agent* agent, float deltaTime)
{
	bool inLair = CheckCollisionPointRec({ agent->GetPosition().x, agent->GetPosition().y }, agent->GetNavMesh()->GetLair());
	bool meantTo = agent->PathComplete();
	if (inLair &&  meantTo)
	{
		for (Agent* t : m_children)
		{
			bool there = CheckCollisionPointRec({ t->GetPosition().x, t->GetPosition().y }, t->GetNavMesh()->GetLair());
			if (!there)
			{
				return !m_targetsThere;
			}
		}
		return m_targetsThere;
	}
	return false;
}