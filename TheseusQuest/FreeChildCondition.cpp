#include "FreeChildCondition.h"

bool FreeChildCondition::isTrue(Agent* agent, float deltaTime)
{
	float closest = UINT32_MAX;
	for (Agent* t : m_children)
	{
		float dist = glm::distance(agent->GetPosition(), t->GetPosition());
		if (dist < closest)
		{
			closest = dist;
		}
	}
	float dist = glm::distance(agent->GetPosition(), m_player->GetPosition());
	return closest <= m_distance && dist <= m_distance;	
}
