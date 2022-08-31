#include "GoToPointBehaviour.h"
#include "raylib.h"
#include "Agent.h"
#include <iostream>

void GoToPointBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete())
	{
		std::cout << agent->name + " has entered a GoToPoint behaviour going to " << m_point.x << "," << m_point.y << std::endl;

		agent->GoTo(m_point);
	}
}

void GoToPointBehaviour::Enter(Agent* agent)
{
	std::cout << agent->name + " has entered a GoToPoint behaviour" << std::endl;

	agent->Reset();
}