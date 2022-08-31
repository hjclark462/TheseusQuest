#pragma once
#include "Behaviour.h"
class WASDBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Enter(Agent* agent);
};

