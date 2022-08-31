#pragma once
#include "Condition.h"
class CaughtByMinotaurCondition : public Condition
{
private:
	float m_distance;
	std::vector<Agent*> m_targets;
	bool m_lessThan;

public:
	CaughtByMinotaurCondition(float d, Agent* agent, std::vector<Agent*> targets);	
	virtual bool IsTrue(Agent* agent, float deltaTime);
};
