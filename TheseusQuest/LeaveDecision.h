#pragma once
#include "Decision.h"
class LeaveDecision : public Decision
{
	virtual void MakeDecision(Agent* agent, float deltaTime);
};

