#pragma once
#include "Condition.h"
class FreeChildCondition : public Condition
{
	float m_distance;
	Agent* m_player;
	std::vector<Agent*> m_children;
public:
	FreeChildCondition(float distance, Agent* player, std::vector<Agent*> children) : m_distance(distance), m_player(player), m_children(children) {}
	virtual bool isTrue(Agent* agent, float deltaTime);
};

