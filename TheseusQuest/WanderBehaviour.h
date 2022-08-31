#pragma once
#include "Behaviour.h"
#include "Agent.h"
#include "Utilities.h"

class WanderBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Enter(Agent* agent);
	virtual float Evaluate(Agent* agent);
};
