#pragma once
#include <vector>
#include "Behaviour.h"
#include "State.h"

class Agent;

class FiniteStateMachine : public Behaviour
{
private:
	std::vector<State*> m_states;

	State* m_currentState;
	State* m_newState;

public:
	FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) { m_states.push_back(s); }
	virtual ~FiniteStateMachine();
	
	void AddState(State* state){ m_states.push_back(state); };
	
	void Enter(Agent* agent){ m_currentState->Enter(agent); };
	void Update(Agent* agent, float deltaTime);
};