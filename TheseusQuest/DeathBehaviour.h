#pragma once
#include "Behaviour.h"
class DeathBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime) {}
	virtual void Enter(Agent* agent);
	virtual void Exit(Agent* agent);
};

