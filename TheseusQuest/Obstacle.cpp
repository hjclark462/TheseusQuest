#include "Obstacle.h"

void Obstacle::Draw(Color obstacleColor)
{
	// Draw each edge as a line
	for (auto edge : m_edges)
	{
		DrawLine((int)edge.first.x, (int)edge.first.y, (int)edge.second.x, (int)edge.second.y, obstacleColor);		
	}
}