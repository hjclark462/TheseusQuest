#pragma once
#include <vector>
#include "raylib.h"

class Obstacle 
{
public:		
	std::vector<Vector2> m_points;	
	std::vector <std::pair<Vector2, Vector2>> m_edges;	
		
	Obstacle(std::vector<Vector2> points, std::vector <std::pair<Vector2, Vector2>> edges, float padding) : m_points(points),  m_edges(edges){}
	void Draw(Color obstacleColor);	
};

