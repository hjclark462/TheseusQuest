#pragma once
#include "Condition.h"

class ReturnedCondition : public Condition
{
private:
	bool m_targetsThere;
	std::vector<Agent*> m_children;
public:
	ReturnedCondition(std::vector<Agent*> targets, bool targetsThere) : m_children(targets), m_targetsThere(targetsThere) {}
	virtual bool IsTrue(Agent* agent, float deltaTime);
};