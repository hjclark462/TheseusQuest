#include "DistanceCondition.h"

DistanceCondition::DistanceCondition(float d, Agent* agent, std::vector<Agent*> targets, bool lt) : m_distance(d), m_children(targets), m_lessThan(lt)
{
	m_children.push_back(agent);
}

DistanceCondition::DistanceCondition(float d, Agent* agent, bool lt) : m_distance(d), m_lessThan(lt)
{
	m_children.push_back(agent);
}

bool DistanceCondition::IsTrue(Agent* agent, float deltaTime)
{
	float closest = UINT32_MAX;
	for (Agent* t : m_children)
	{
		if (CheckCollisionPointRec({ t->GetPosition().x, t->GetPosition().y }, agent->GetNavMesh()->GetLair()) ||
			(agent->GetNavMesh()->LineIntersectsObstacle(agent->GetPosition(), t->GetPosition())))
		{
			continue;
		}
		float dist = glm::distance(agent->GetPosition(), t->GetPosition());
		if (dist < closest)
		{
			closest = dist;
		}
	}
	return (closest <= m_distance) == m_lessThan;
}