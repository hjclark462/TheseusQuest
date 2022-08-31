#pragma once
#include "Condition.h"
class InLairCondition : public Condition
{
public:
	virtual bool IsTrue(Agent* agent, float deltaTime);
};

