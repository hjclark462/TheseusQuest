#include "DazeBehaviour.h"
#include <iostream>

void DazeBehaviour::Enter(Agent* agent)
{
	std::cout << agent->name + " has entered a dazed behaviour" << std::endl;
}

void DazeBehaviour::Update(Agent* agent, float deltaTime)
{
	agent->ClearPath();
}

void DazeBehaviour::Exit(Agent* agent)
{

}
