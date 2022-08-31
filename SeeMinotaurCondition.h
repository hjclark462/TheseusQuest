#pragma once
#include "Condition.h"
class SeeMinotaurCondition : public Condition
{
public:
	virtual bool IsTrue(Agent* agent, float deltaTime);
};

