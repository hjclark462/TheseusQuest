#pragma once
#include "Decision.h"
class CaughtDecision : public Decision
{
	virtual void MakeDecision(Agent* agent, float deltaTime);
};

