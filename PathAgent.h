#pragma once
#include "glm/glm.hpp"
#include <vector>
#include "Pathfinding.h"
#include "NavMesh.h"
using namespace AIForGames;

class PathAgent
{
private:
	glm::vec2 m_position;

	std::vector<Node*> m_path;
	std::vector<glm::vec2> m_smoothPath;
	int m_currentIndex;
	Node* m_currentNode;

	float m_speed;	
	NavMesh* m_navMesh;
		
public:	
	PathAgent();

	void SetSpeed(float speed){ m_speed = speed; }
	void SetPosition(glm::vec2 position){ m_position = position; }
	void SetNavMesh(NavMesh* navMesh){	m_navMesh = navMesh; }

	void Update(float deltaTime);
	void GoToPoint(glm::vec2 point);

	NavMesh* GetNavMesh() { return m_navMesh; }
	std::vector<Node*>& GetPath() { return m_path; }
	std::vector<glm::vec2>& GetSmoothPath() { return m_smoothPath; }
	glm::vec2 GetPosition() { return m_position; }
	float GetSpeed() { return m_speed; }
	glm::vec2 GetNextNodePosition() { return m_path[m_currentIndex]->position; }
	void ClearPath();
};
