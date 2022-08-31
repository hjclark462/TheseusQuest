#pragma once
#include <vector>

class Behaviour;
class Condition;
class Agent;

class State
{
public:
	struct Transition
	{
		Condition* condition;
		State* targetState;
	};

private:
	std::vector<Behaviour*> m_behaviours;
	std::vector<Transition> m_transitions;

public:
	State();
	State(Behaviour* b) { m_behaviours.push_back(b); }
	~State();
	void AddBehaviour(Behaviour* b) { m_behaviours.push_back(b); }
	void AddTransition(Condition* condition, State* targetState);

	const std::vector<Transition> GetTransitions() { return m_transitions; }

	void Enter(Agent* agent);
	void Update(Agent* agent, float deltaTime);
	void Exit(Agent* agent);
};
