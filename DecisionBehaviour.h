#pragma once
#include "Behaviour.h"
#include "Decision.h"
#include <iostream>

class DecisionBehaviour : public Behaviour
{
	Decision* m_decision;
public:
	DecisionBehaviour(Decision* decision) : m_decision(decision) {}
	void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);
};

