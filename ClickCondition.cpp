#include "ClickCondition.h"

ClickCondition::ClickCondition(bool m) : m_mouse(m)
{
	
}

bool ClickCondition::IsTrue(Agent* agent)
{
	return IsMouseButtonPressed(0);
}