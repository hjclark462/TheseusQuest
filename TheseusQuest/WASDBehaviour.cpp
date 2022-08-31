#include "WASDBehaviour.h"
#include "raylib.h"

void WASDBehaviour::Update(Agent* agent, float deltaTime)
{
	glm::vec2 input(IsKeyDown(KEY_D) - IsKeyDown(KEY_A), IsKeyDown(KEY_S) - IsKeyDown(KEY_W));

	if (!(glm::length(input) < 1))
	{
		input = glm::normalize(input);
		glm::vec2 newPos = agent->GetPosition() += (input * agent->GetSpeed() * deltaTime);
		if (agent->GetNavMesh()->GetNode(newPos) != nullptr)
		{
			agent->SetPosition(newPos);
		}
		
	}
}

void WASDBehaviour::Enter(Agent* agent)
{
	agent->SetPosition(agent->GetOriginalPosition());
}
