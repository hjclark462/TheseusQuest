#pragma once
#include "Condition.h"
class NoLineOfSightCondition : public Condition
{
	std::vector<Agent*> m_children;
public:
	NoLineOfSightCondition(Agent* player, std::vector<Agent*> children) : m_children(children) { m_children.push_back(player); }
	virtual bool IsTrue(Agent* agent, float deltaTime);
};

