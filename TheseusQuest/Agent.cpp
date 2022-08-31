#include "Agent.h"
#include "Behaviour.h"

Agent::Agent(NavMesh* navMesh, Behaviour* behaviour, float bravery, float speed, glm::vec2 position, std::string string)
	: m_current(behaviour), m_navMesh(navMesh), m_color({ 255, 255, 0,255 }), m_braveOriginalScore(bravery),
	m_braveScore(bravery), m_originalSpeed(speed), m_originalPos(position), name(string)
{
	m_pathAgent.SetSpeed(speed);
	m_pathAgent.SetPosition(position);
	m_pathAgent.SetNavMesh(navMesh);	
	m_target = nullptr;
}

// For debugging the unsmoothed path of the pathing agents
std::vector<glm::vec2> Agent::GetJaggedPath()
{
	std::vector<Node*>& path = m_pathAgent.GetPath();
	std::vector<glm::vec2> pathPos;
	for (int i = 0; i < path.size(); i++)
	{
		pathPos.push_back(path[i]->position);
	}
	return pathPos;
}

void Agent::Update(float deltaTime)
{
	// Update Behaviours
	if (m_current)
	{
		m_current->Update(this, deltaTime);
	}	
	m_pathAgent.Update(deltaTime);
}

void Agent::Draw()
{
	DrawCircle(m_pathAgent.GetPosition().x, m_pathAgent.GetPosition().y, m_size, m_color);
}

void Agent::GoTo(glm::vec2 point)
{
	m_pathAgent.GoToPoint(point);
}

void Agent::RaiseBravery(float deltaTime)
{
	m_braveScore = m_braveScore - deltaTime;
}

void Agent::ResetBravery() 
{
	// For resetting the bravery once they are scared again so they don't leave straight away
	m_braveScore = m_braveOriginalScore; 
	m_pathAgent.SetSpeed(m_originalSpeed);
}
