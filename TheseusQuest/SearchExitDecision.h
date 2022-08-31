#pragma once
#include "Decision.h"
class SearchExitDecision : public Decision
{
	virtual void MakeDecision(Agent* agent, float deltaTime);
};

