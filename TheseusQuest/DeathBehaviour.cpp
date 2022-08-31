#include "DeathBehaviour.h"
#include "raylib.h"

void DeathBehaviour::Enter(Agent* agent)
{
	agent->SetPosition(agent->GetOriginalPosition());
	agent->RemoveLife();	
}

void DeathBehaviour::Exit(Agent* agent) 
{
	if (agent->GetLives() <= 0)
	{
		CloseWindow();
	}
}

