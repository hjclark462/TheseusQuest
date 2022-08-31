#include "SearchExitDecision.h"
#include "Utilities.h"

void SearchExitDecision::MakeDecision(Agent* agent, float deltaTime)
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
		std::cout << agent->name + " is searching for the exit" << std::endl;
	}
}

