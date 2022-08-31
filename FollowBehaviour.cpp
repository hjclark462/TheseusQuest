#include "FollowBehaviour.h"
#include <iostream>

void FollowBehaviour::Update(Agent* agent, float deltaTime)
{
	// check if the agent has moved significantly from its last position. if so we want to repath towards it
	float closestDist = glm::distance(m_followTarget->GetPosition(), agent->GetPosition());
	Agent* closestTarget = m_followTarget;

	for (Agent* t : m_children)
	{
		float dist = glm::distance(agent->GetPosition(), t->GetPosition());
		if (dist < closestDist)
		{
			closestDist = dist;
			closestTarget = t;
		}
	}

	m_followTarget = closestTarget;
	lastTargetPosition = m_followTarget->GetPosition();
	
	if (glm::distance(agent->GetPosition(), m_player->GetPosition()) <= 500 &&
		!agent->GetNavMesh()->LineIntersectsObstacle(agent->GetPosition(), m_player->GetPosition()))
	{
		m_followTarget = m_player;
		lastTargetPosition = m_player->GetPosition();
	}


	if (!agent->GetNavMesh()->LineIntersectsObstacle(agent->GetPosition(), m_followTarget->GetPosition()) && closestDist != 0)
	{
		lastTargetPosition = m_followTarget->GetPosition();
		agent->GoTo(m_followTarget->GetPosition());
	}	
	else
	{
		agent->GoTo(lastTargetPosition);
	}
}

void FollowBehaviour::Enter(Agent* agent)
{
	agent->SetTarget(m_followTarget);
	lastTargetPosition = m_followTarget->GetPosition();
	agent->Reset();
	agent->GoTo(lastTargetPosition);
}

float FollowBehaviour::Evaluate(Agent* agent)
{
	if (agent->GetNavMesh()->LineIntersectsObstacle(agent->GetPosition(), m_followTarget->GetPosition()) &&
		!CheckCollisionPointRec({m_followTarget->GetPosition().x, m_followTarget->GetPosition().y}, agent->GetNavMesh()->GetLair()))
	{
		float dist = glm::distance(m_followTarget->GetPosition(), agent->GetPosition());
		float eval = (5 * m_followTarget->GetSize()) - dist * m_weight;
		if (eval < 0)
		{
			eval = 0;
		}
		return eval;
	}
	return 0;
}