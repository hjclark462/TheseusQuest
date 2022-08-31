#pragma once
#include "Decision.h"
class ScaredDecision : public Decision
{
	glm::vec2 m_startPos;
public:
	virtual void MakeDecision(Agent* agent, float deltaTime);
};

