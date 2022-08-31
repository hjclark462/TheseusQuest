#include "WanderBehaviour.h"
#include <iostream>

void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete())
	{
		glm::vec2 pos;

		float x = Utilities::Random(10, GetScreenWidth() - 10);
		float y = Utilities::Random(10, GetScreenHeight() - 10);
		pos = { x, y };
		Node* inNode = agent->GetNavMesh()->GetNode(pos);
		if (inNode != nullptr)
		{
			agent->GoTo(pos);
		}
	}
}

void WanderBehaviour::Enter(Agent* agent)
{
	
		std::cout << agent->name + " has entered a wander behaviour" << std::endl;
	
	agent->Reset();
}

float WanderBehaviour::Evaluate(Agent* agent)
{
	Agent* target = agent->GetTarget();
	float dist = glm::distance(target->GetPosition(), agent->GetPosition());

	float eval = dist;
	if (eval < 0)
	{
		eval = 0;
	}
	return eval;
}