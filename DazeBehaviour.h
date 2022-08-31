#pragma once
#include "Behaviour.h"
class DazeBehaviour : public Behaviour
{	
public:
	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Exit(Agent* agent);
};

