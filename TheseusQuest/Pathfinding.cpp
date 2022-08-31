#include "Pathfinding.h"
#include <iostream>


namespace AIForGames
{
	// Predicate functions for sorting
	bool gSorter(Node* a, Node* b)
	{
		return a->gScore > b->gScore;
	}

	bool fSorter(Node* a, Node* b)
	{
		return a->fScore > b->fScore;
	}

	int Node::GetAdjacentVertices(Node* other, glm::vec2* adjacent)
	{
		int count = 0;
		for (auto v : vertices)
		{
			for (auto v2 : other->vertices)
			{
				if (v.x == v2.x && v.y == v2.y)
				{
					adjacent[count++] = v;
					break;
				}
			}
		}
		return count;
	}

	float Heuristic(Node* node, Node* dest)
	{
		float xDiff = abs(node->position.x - dest->position.x);
		float yDiff = abs(node->position.y - dest->position.y);
		
		return xDiff + yDiff;
	}

	std::vector<Node*> AStarSearch(Node* startNode, Node* endNode)
	{
		int counterA =0;
		
		// Validate the input
		if (startNode == nullptr || endNode == nullptr)
		{
			return std::vector<Node*>();
		}
		if (startNode == endNode)
		{
			std::vector<Node*> singularPath;
			singularPath.push_back(startNode);
			startNode->closeListed = true;
			return singularPath;
		}

		// Initialise the starting node
		startNode->gScore = 0;
		startNode->previous = nullptr;

		// Temp Lists
		std::vector<Node*> openList;
		std::vector<Node*> closedList;
		Node* currentNode = nullptr;
		// Start node in temp list
		startNode->openListed = true;
		openList.push_back(startNode);

		while (!openList.empty())
		{			
			counterA++;
			//std::sort(openList.begin(), openList.end(), fSorter);
			
			currentNode = openList.front();		
			std::pop_heap(openList.begin(), openList.end(), fSorter);
			openList.pop_back();
			currentNode->closeListed = true;
			closedList.push_back(currentNode);

			// If we visit the endNode, then we can exit early. Sorting the openList above guarantees the 
			// shortest path is found, given no negative costs (a prerequisite of the algorithm). 
			if (currentNode == endNode)
			{
				break;
			}

			for (Edge c : currentNode->connections)
			{

				if (std::find(closedList.begin(), closedList.end(), c.m_target) == closedList.end())
				{
					float gScore = currentNode->gScore + c.cost;
					float hScore = Heuristic(c.m_target, endNode);
					float fScore = gScore + hScore;

					// Have not yet visited the node. So calculate the Score and update its parent.
					// Also add it to the openList for processing.
					if (std::find(openList.begin(), openList.end(), c.m_target) == openList.end())
					{
						c.m_target->gScore = gScore;
						c.m_target->fScore = fScore;
						c.m_target->previous = currentNode;
						c.m_target->openListed = true;
						openList.push_back(c.m_target);						
					}
					// Node is already in the openList with a valid Score. So compare the calculated Score 
					// with the exisitng to find the shorter path.
					else if (fScore < c.m_target->fScore)
					{
						c.m_target->gScore = gScore;
						c.m_target->fScore = fScore;
						c.m_target->previous = currentNode;
						std::make_heap(openList.begin(), openList.end(), fSorter);
					}
				}
			}
		}

		// Create Path in reverse from endNode to startNode
		std::vector<Node*> path;
		if(currentNode == endNode)
		{
			while (currentNode != nullptr)
			{
				path.insert(path.begin(), currentNode);
				currentNode = currentNode->previous;
			}
		}
		else
		{
			return std::vector<Node*>();
		}
		std::cout << counterA << std::endl;

		return path;
	}

	void DrawPath(std::vector<glm::vec2>& path, Color lineColor)
	{
		for (int i = 1; i < path.size(); i++)
		{
			DrawLine(
				(path[i - 1].x),
				(path[i - 1].y),
				(path[i].x),
				(path[i].y),
				lineColor);
		}
	}
}



