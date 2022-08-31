#pragma once
#include "Condition.h"
class CaughtByMinotaurCondition : public Condition
{
private:
	float m_distance;
	std::vector<Agent*> m_children;
	Agent* m_inotaur;
	
public:
	CaughtByMinotaurCondition(float d, Agent* minotaur, std::vector<Agent*> children) : m_distance(d), m_inotaur(minotaur), m_children(children) {}
	virtual bool IsTrue(Agent* agent, float deltaTime);
};
