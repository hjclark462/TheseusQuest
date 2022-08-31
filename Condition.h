#pragma once
#include "Agent.h"
#include <iostream>

class Condition
{
public:
	virtual bool IsTrue(Agent* agent, float deltaTime) { return true; }
};