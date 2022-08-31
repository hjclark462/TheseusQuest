#include "SelectorBehaviour.h"
#include "Agent.h"

SelectorBehaviour::~SelectorBehaviour()
{
	delete m_b1;
	delete m_b2;
}

void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
	if (m_selected != b)
	{
		m_selected = b;
		agent->Reset();
	}
}

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
	if (true)
	{
		SetBehaviour(m_b2, agent);
	}
	else
	{
		SetBehaviour(m_b1, agent);	
	}
	m_selected->Update(agent, deltaTime);
}