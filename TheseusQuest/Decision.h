#pragma once
#include <iostream>
#include "Agent.h"

class Decision
{
public:
	virtual void MakeDecision(Agent* agent, float deltaTime) {}
};