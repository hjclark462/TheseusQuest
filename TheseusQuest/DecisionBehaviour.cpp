#include "DecisionBehaviour.h"

void DecisionBehaviour::Enter(Agent* agent)
{
	std::cout << agent->name + " has entered a dazed behaviour" << std::endl;
}

void DecisionBehaviour::Update(Agent* agent, float deltaTime)
{
	m_decision->MakeDecision(agent, deltaTime);
}