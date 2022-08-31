#include "CaughtDecision.h"

void CaughtDecision::MakeDecision(Agent* agent, float deltaTime)
{
	agent->SetSpeed(agent->GetTarget()->GetSpeed());
	agent->GoTo(agent->GetOriginalPosition());	
	std::cout << agent->name + " is caught" << std::endl;

}

