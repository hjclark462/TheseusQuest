#include "BraveDecision.h"

void BraveDecision::MakeDecision(Agent* agent, float deltaTime)
{
	agent->RaiseBravery(deltaTime);
	std::cout << agent->name + " is getting braver" << std::endl;
}
