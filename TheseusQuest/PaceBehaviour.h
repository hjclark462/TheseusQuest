#pragma once
#include "SelectorBehaviour.h"
class PaceBehaviour : public SelectorBehaviour
{
public:
	PaceBehaviour(Behaviour* b1, Behaviour* b2) { m_b1 = b1; m_b2 = b2; m_selected = nullptr; }
	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Exit(Agent* agent);
};

