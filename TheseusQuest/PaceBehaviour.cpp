#include "PaceBehaviour.h"
#include <iostream>

void PaceBehaviour::Enter(Agent* agent)
{
	std::cout << agent->name + " has entered a pace behaviour" << std::endl;
}

void PaceBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete())
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

void PaceBehaviour::Exit(Agent* agent)
{
	agent->ClearPath();
}
