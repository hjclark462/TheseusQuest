#pragma once
#include "Pathfinding.h"
#include "poly2tri/poly2tri.h"
#include "Obstacle.h"
#include "Utilities.h"

using namespace AIForGames;

class NavMesh 
{
public:
	//creates the base walkable area
	NavMesh(float width, float height);
	~NavMesh();

	// returns true if the obstacle was added safely (does not overlap or exceed the bounds of the screen)
	bool AddObstacle(std::vector<Vector2> points, float padding);
	// The manual making of this games obstacles
	void MakeMaze();
	void Build();
	void Draw(bool connections);
	
	glm::vec2 GetRandomPosition();
	Node* FindClosest(float x, float y) const;
	float TriArea(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);
	int PointOrientation(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);
	bool PointInTri(const glm::vec2* pt, const glm::vec2* v1, const glm::vec2* v2, const glm::vec2* v3);
	Node* GetNode(glm::vec2 position);
	Node* GetClosestNode(glm::vec2 worldPos) { return FindClosest(worldPos.x, worldPos.y); }
	Rectangle GetLair() { return m_lair; }
	Rectangle GetExit() { return m_exit; }
	std::vector<Node*> GetNodes() { return m_nodes; }
	bool LineIntersectsObstacle(glm::vec2 pos1, glm::vec2 pos2);
	
	std::vector<glm::vec2> SmoothPath(glm::vec2 start, glm::vec2 end, const std::vector<Node*>& path, std::vector<glm::vec2>& smoothPath);

    float triarea2(glm::vec2 a, glm::vec2 b, glm::vec2 c);
    bool vequal(glm::vec2 a, glm::vec2 b);
	int stringPull(glm::vec2* portals, int nportals, std::vector<glm::vec2>& pts);

	
private:
	std::vector<Obstacle> m_obstacles;
	std::vector<Node*> m_nodes;
	Rectangle m_lair = { 600, 410, 375, 200 };
	Rectangle m_exit = { 1340, 640, 260, 300 };
	// this is used for building the mesh uses Poly2Tri (https://github.com/greenm01/poly2tri)
	p2t::CDT* m_cdt;
	std::vector<std::vector<p2t::Point*>> m_polygons;		
};

