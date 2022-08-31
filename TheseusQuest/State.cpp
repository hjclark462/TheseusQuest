#include "State.h"
#include "Behaviour.h"
#include "Condition.h"
#include <iostream>

State::~State()
{
	// we own the behaviours assigned to us
	for (Behaviour* b : m_behaviours)
	{
		delete b;
	}

	// we also own the Conditions in each Transition
	// (but the states are references, so don't clean them up here)
	for (Transition t : m_transitions)
	{
		delete t.condition;
	}
}

void State::AddTransition(Condition* condition, State* targetState)
{
	Transition transition;
	transition.condition = condition;
	transition.targetState = targetState;
	m_transitions.push_back(transition);
}

void State::Enter(Agent* agent)
{
	for (Behaviour* b : m_behaviours)
	{
		b->Enter(agent);
	}
}

void State::Update(Agent* agent, float deltaTime)
{

	for (Behaviour* b : m_behaviours)
	{
		b->Update(agent, deltaTime);
	}
}

void State::Exit(Agent* agent)
{
	for (Behaviour* b : m_behaviours)
	{
		b->Exit(agent);
	}
}
