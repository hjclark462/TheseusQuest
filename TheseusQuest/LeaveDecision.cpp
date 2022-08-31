#include "LeaveDecision.h"

void LeaveDecision::MakeDecision(Agent* agent, float deltaTime)
{
	if (agent->GetPosition().y != GetScreenHeight() - agent->GetSize())
	{
		agent->ClearPath();
		agent->SetPosition({ agent->GetPosition().x, agent->GetPosition().y + agent->GetSpeed() * deltaTime });
	}
	std::cout << agent->name + " is free" << std::endl;
}

