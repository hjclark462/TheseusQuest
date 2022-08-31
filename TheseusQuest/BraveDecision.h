#pragma once
#include "Decision.h"
class BraveDecision : public Decision
{
	virtual void MakeDecision(Agent* agent, float deltaTime);
};

