#pragma once
#include "Decision.h"
#include "Condition.h"

class ABDecision : public Decision
{
	Decision* m_A;
	Decision* m_B;
	Condition* m_condition;
public:
	ABDecision(Condition* condition, Decision* A, Decision* B) : m_condition(condition), m_A(A), m_B(B) {}
	virtual void MakeDecision(Agent* agent, float deltaTime);
};