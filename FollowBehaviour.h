#pragma once
#include "Behaviour.h"
#include "Agent.h"

class FollowBehaviour : public Behaviour
{
public:
	FollowBehaviour(Agent* target, float weight) : m_followTarget(target), m_weight(weight) {}
	FollowBehaviour(Agent* target, std::vector<Agent*> targets, float weight) : 
		m_player(target), m_followTarget(target), m_weight(weight), m_children(targets) {}
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Enter(Agent* agent);
	
	virtual float Evaluate(Agent* agent);
private:
	glm::vec2 lastTargetPosition;
	std::vector<Agent*> m_children;
	Agent* m_player;
	Agent* m_followTarget;
	float m_weight;
};
