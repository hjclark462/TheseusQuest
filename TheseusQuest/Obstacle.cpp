#include "Obstacle.h"

void Obstacle::Draw(Color obstacleColor)
{
	// Draw each edge as a line
	for (auto edge : m_edges)
	{
		DrawLineEx(edge.first, edge.second, 2, obstacleColor);		
	}
}