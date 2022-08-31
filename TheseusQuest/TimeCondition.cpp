#include "TimeCondition.h"

bool TimeCondition::IsTrue(Agent* agent, float deltaTime)
{
	m_timer = m_timer - deltaTime;
	if (m_timer < 0)
	{
		m_timer = m_startTime;
		return true;
	}
	else
	{
		return false;
	}
}
