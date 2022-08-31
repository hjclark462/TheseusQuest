#pragma once
#include "Condition.h"
class LeaveCondition : public Condition
{
	virtual bool IsTrue(Agent* agent, float deltaTime);
};

