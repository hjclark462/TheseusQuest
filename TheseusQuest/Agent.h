#pragma once
#include "PathAgent.h"
#include "NavMesh.h"
#include "glm/glm.hpp"
#include "Obstacle.h"
#include <string>

using namespace AIForGames;
class Behaviour;

class Agent
{
private:
	PathAgent m_pathAgent;
	Behaviour* m_current;
	NavMesh* m_navMesh;

	Agent* m_target;
	std::vector<Agent*> m_children;

	Color m_color;
	int m_size;
	int m_lives = 3;

	glm::vec2 m_originalPos;

	float m_originalSpeed;

	float m_braveScore;
	float m_braveOriginalScore;

public:
	Agent(NavMesh* navMesh, Behaviour* behaviour, float bravery, float speed, glm::vec2 position, std::string name);
	void Update(float deltaTime);
	void Draw();

	// Initiates path finding by the path agent
	void GoTo(glm::vec2 point);
	
	// Funcitons that aren't just setters or getters.
	void Reset() {m_pathAgent.GetPath().clear(); }
	bool PathComplete() { return m_pathAgent.GetSmoothPath().empty(); }
	void ClearPath() { m_pathAgent.ClearPath(); }
	void RaiseBravery(float deltaTime);
	void ResetBravery();
	void RemoveLife() { m_lives--; }

	// Setters
	void SetNavMesh(NavMesh* navMesh) { m_navMesh = navMesh; }
	void SetBehaviour(Behaviour* b) { m_current = b; }
	void SetSpeed(float speed) { m_pathAgent.SetSpeed(speed); }
	void SetColor(Color col) { m_color = col; }
	void SetSize(int size) { m_size = size; }
	void SetTarget(Agent* target) { m_target = target; }
	void SetOriginalPosition(glm::vec2 position) { m_originalPos = position; }
	void SetPosition(glm::vec2 position) { m_pathAgent.SetPosition(position); }
	
	// Getters
	NavMesh* GetNavMesh() { return m_navMesh; }
	std::vector<glm::vec2>& GetPath() { return m_pathAgent.GetSmoothPath(); }
	std::vector<glm::vec2> GetJaggedPath();
	glm::vec2 GetOriginalPosition() { return m_originalPos; }
	glm::vec2 GetPosition() { return m_pathAgent.GetPosition(); }
	int GetLives() { return m_lives; }
	float GetSpeed() { return m_pathAgent.GetSpeed(); }
	Agent* GetTarget() { return m_target; }
	std::vector<Agent*> GetTargets() { return m_children; }
	Color GetColor() { return m_color; }
	int GetSize() { return m_size; }
	float GetBravery() { return m_braveScore; }

	// For debug reasons
	std::string name;
};