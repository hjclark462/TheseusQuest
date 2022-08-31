#pragma once
#include "Condition.h"
class BraveryCondition : public Condition
{
public:
	virtual bool IsTrue(Agent* agent, float deltaTime);
};

