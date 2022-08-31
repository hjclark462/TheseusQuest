#pragma once
#include "Behaviour.h"
class GoToPointBehaviour : public Behaviour
{
	glm::vec2 m_point;
public:
	GoToPointBehaviour(glm::vec2 point) : m_point(point) {}
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Enter(Agent* agent);
};

