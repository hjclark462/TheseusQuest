#pragma once
#include "Condition.h"
class TimeCondition : public Condition
{
	float m_timer;
	float m_startTime;
public:
	TimeCondition(float timer) : m_timer(timer), m_startTime(timer) {};
	virtual bool IsTrue(Agent* agent, float deltaTime);
};