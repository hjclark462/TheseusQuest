#include "PathAgent.h"

PathAgent::PathAgent() : m_currentIndex(-1), m_currentNode(nullptr), m_speed(100.0f),
	m_navMesh(nullptr)
{
	m_position.x = 0;
	m_position.y = 0;
}

void PathAgent::Update(float deltaTime)
{
	if (m_smoothPath.empty())
	{
		return;
	}

	// Calculate the distance to next node and the unit vector to that node
	glm::vec2 delta = m_smoothPath[m_currentIndex] - m_position;
	float distance = glm::length(delta);

	// Normalize the vector to the next node
	if (distance > 0)
	{
		delta /= distance;		
	}

	//Subtract speed * deltaTime from the distance (how much we're going to move this frame)
	distance -= m_speed * deltaTime;
	// If the distance is greater than zero, then this frame we're just moving towards the target node. 
	if (distance >= 0)
	{
		// Add speed*deltaTime*unit vector to our position.
		m_position += delta * m_speed * deltaTime;
	}

	// Otherwise we've overshot the node. Add one to the currentIndex, If we've reached the end of out 
	// path, snap to the final node and empty the path so future updates do nothing.
	else
	{
		m_currentIndex++;
		if (m_currentIndex >= m_smoothPath.size())
		{
			m_position = m_smoothPath[m_currentIndex-1];
			m_smoothPath.clear();
		}
		// If we have a next node, then distance with the subtracted speed*deltaTime tells us how far we've 
		// overshot the node if we invert it. 
		else
		{
			// Find the unit vector from our previous node to the new next
			// node, and move along this vector by the overshoot distance from the previous next node.
			delta = m_smoothPath[m_currentIndex] - m_smoothPath[m_currentIndex - 1];
			if (glm::length(delta) > 0)
			{
				delta = glm::normalize(delta);
			}

			m_position = m_smoothPath[m_currentIndex - 1] + delta * -distance;
		}
	}
}

void PathAgent::GoToPoint(glm::vec2 point)
{	
	Node* startNode = m_navMesh->GetNode(m_position);
	// Accounts for the agent being off of the NavMesh
	if (startNode == NULL)
	{
		startNode = m_navMesh->GetClosestNode(m_position);
	}
	Node* endNode = m_navMesh->GetNode(point);
	// Figure out the shortest path using AStar and then feed it into the SmoothPath algorithm
	m_path = AStarSearch(startNode, endNode);
	
	std::vector<glm::vec2> smooth = m_navMesh->SmoothPath(m_position, point, m_path, m_smoothPath);
	m_currentIndex = 0;
}

void PathAgent::ClearPath()
{
	// Reset the paths
	m_smoothPath.clear(); 
	m_path.clear();
}

