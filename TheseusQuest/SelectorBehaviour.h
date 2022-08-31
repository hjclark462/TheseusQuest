#pragma once
#include "Behaviour.h"

class SelectorBehaviour : public Behaviour
{
protected:
	Behaviour* m_b1 = nullptr;
	Behaviour* m_b2 = nullptr;
	Behaviour* m_selected = nullptr;

public:
	SelectorBehaviour() {}
	SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2), m_selected(nullptr) {}
	~SelectorBehaviour();
	
	virtual void Update(Agent* agent, float deltaTime);
	
	void SetBehaviour(Behaviour* b, Agent* agent);
};