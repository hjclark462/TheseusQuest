#include "ScaredDecision.h"
#include "Utilities.h"

void ScaredDecision::MakeDecision(Agent* agent, float deltaTime)
{
	agent->ResetBravery();
	if (agent->PathComplete())
	{
		agent->GoTo({agent->GetOriginalPosition().x + Utilities::Random(0, 2), 
			agent->GetOriginalPosition().y + Utilities::Random(0, 2) });
	}
	std::cout << agent->name + " is scared" << std::endl;
}
