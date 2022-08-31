#pragma once
#include "Condition.h"

class DistanceCondition : public Condition
{
private:
	float m_distance;
	std::vector<Agent*> m_children;
	bool m_lessThan;

public:
	DistanceCondition(float d, std::vector<Agent*> targets, bool lt) :m_distance(d), m_children(targets), m_lessThan(lt) {};
	DistanceCondition(float d, Agent* agent, std::vector<Agent*> targets, bool lt);
	DistanceCondition(float d, Agent* agent, bool lt);
	virtual bool IsTrue(Agent* agent, float deltaTime);
};
