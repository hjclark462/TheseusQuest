#pragma once
#include "SelectorBehaviour.h"
class ReturnBehaviour : public SelectorBehaviour
{
	Agent* m_stopTarget;
public:
	ReturnBehaviour(Behaviour* b1, Behaviour* b2, Agent* stopTarget) { m_b1 = b1; m_b2 = b2; m_stopTarget = stopTarget; m_selected = nullptr; }
	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);
};

