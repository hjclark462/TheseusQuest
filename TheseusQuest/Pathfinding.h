#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include "Utilities.h"

namespace AIForGames
{
	struct Node;

	struct Edge
	{
		Edge() { m_target = nullptr, cost = 0; }
		Edge(Node* _node, float _cost) : m_target(_node), cost(_cost) {}

		Node* m_target;
		float cost;
	};

	struct Node
	{
		Node() {}
		Node(float x, float y) { position.x = x, position.y = y, gScore = 0, previous = nullptr; }
		glm::vec2 position = {0,0};

		float gScore = 0.0f;
		float hScore = 0.0f;
		float fScore = 0.0f;
		Node* previous = nullptr;

		bool openListed = false;
		bool closeListed = false;

		int tracker;

		std::vector<Edge> connections;
		std::vector<glm::vec2> vertices;

		int GetAdjacentVertices(Node* other, glm::vec2* adjacent);
		void ConnectTo(Node* other, float cost) {connections.push_back(Edge(other, cost));}
	};
	
	std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);
	void DrawPath(std::vector<glm::vec2>& path, Color lineColor);
}



