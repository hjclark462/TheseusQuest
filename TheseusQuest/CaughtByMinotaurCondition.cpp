#include "CaughtByMinotaurCondition.h"

bool CaughtByMinotaurCondition::IsTrue(Agent* agent, float deltaTime)
{
	float closest = UINT32_MAX;
	for (Agent* t : m_children)
	{		
		float dist = glm::distance(m_inotaur->GetPosition(), t->GetPosition());
		if (dist < closest)
		{
			closest = dist;
		}
	}
	float dist = glm::distance(agent->GetPosition(), m_inotaur->GetPosition());
	return closest >= m_distance && dist <= m_distance;
}