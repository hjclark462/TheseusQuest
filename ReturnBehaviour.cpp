#include "ReturnBehaviour.h"
#include <iostream>

void ReturnBehaviour::Enter(Agent* agent)
{
	std::cout << agent->name + " has entered a Return behaviour" << std::endl;
}


void ReturnBehaviour::Update(Agent* agent, float deltaTime)
{
	float distance = glm::distance(agent->GetPosition(), m_stopTarget->GetPosition());

	if (distance <= (agent->GetSize()/2) + (m_stopTarget->GetSize()))
	{
		if (m_selected == m_b1)
		{
			SetBehaviour(m_b2, agent);
		}
		else
		{
			SetBehaviour(m_b1, agent);
		}
	}
	m_selected->Update(agent, deltaTime);
}
