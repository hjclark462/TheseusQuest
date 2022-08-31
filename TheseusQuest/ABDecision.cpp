#include "ABDecision.h"

void ABDecision::MakeDecision(Agent* agent, float deltaTime)
{
	if (m_condition->IsTrue(agent, deltaTime))
	{
		m_A->MakeDecision(agent, deltaTime);
	}
	else
	{
		m_B->MakeDecision(agent, deltaTime);
	}
}