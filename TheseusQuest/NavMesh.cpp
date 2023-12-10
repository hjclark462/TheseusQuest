#include "NavMesh.h"
#include "Utilities.h"
#include <vector>
#include <string>
#include <iostream>

NavMesh::NavMesh(float width, float height)
{
	// Creates the base area of the NavMesh Obstacles cannot exceed these bounds
	m_polygons.push_back({});
	m_polygons[0].push_back(new p2t::Point(1, 1));
	m_polygons[0].push_back(new p2t::Point(1, height - 1));
	m_polygons[0].push_back(new p2t::Point(width - 1, height - 1));
	m_polygons[0].push_back(new p2t::Point(width - 1, 1));

	m_cdt = new p2t::CDT(m_polygons[0]);
}

NavMesh::~NavMesh()
{
	for (Node* n : m_nodes)
	{
		delete n;
	}
}

bool NavMesh::AddObstacle(std::vector<Vector2> points, float padding)
{
	// New vector to store the vec2 contained in points witht the padding added to them.
	std::vector<Vector2> paddedPoints;

	for (int i = 0; i < points.size(); i++)
	{
		int prev = i - 1;
		int next = i + 1;
		Vector2 paddedPoint;
		if (i == 0)
		{
			// Starting at the top left point. Points has been added in order.
			paddedPoint = { points[i].x + padding, points[i].y - padding };
		}
		else if (next >= points.size())
		{
			// The the last point in the loop to connect it to the first corner
			if (points[i].x < points[prev].x)
			{
				paddedPoint = { points[i].x + padding, points[i].y - padding };
			}
			else
			{
				paddedPoint = { points[i].x + padding, points[i].y + padding };
			}
		}
		// If the point is to the left of the last point that was padded
		else if (points[i].x < points[prev].x)
		{
			// If the point goes north next
			if (points[i].y > points[next].y)
			{
				paddedPoint = { points[i].x + padding, points[i].y - padding };
			}
			// If the point goes south next
			else
			{
				paddedPoint = { points[i].x - padding,  points[i].y - padding };
			}
		}
		// If the point is to the south of the last point that was padded
		else if (points[i].y > points[prev].y)
		{
			// If the point goes right next
			if (points[i].x < points[next].x)
			{
				paddedPoint = { points[i].x - padding, points[i].y + padding };
			}
			// If the point goes left next
			else
			{
				paddedPoint = { points[i].x - padding, points[i].y - padding };
			}
		}
		// If the point is to the right of the last point that was padded
		else if (points[i].x > points[prev].x)
		{
			// If the point goes south next
			if (points[i].y < points[next].y)
			{
				paddedPoint = { points[i].x - padding, points[i].y + padding };
			}
			// If the point goes north next
			else
			{
				paddedPoint = { points[i].x + padding, points[i].y + padding };
			}
		}
		// If the point is to the north of the last point that was padded
		else
		{
			// If the point goes right next
			if (points[i].x < points[next].x)
			{
				paddedPoint = { points[i].x + padding, points[i].y + padding };
			}
			// If the point goes left next
			else
			{
				paddedPoint = { points[i].x + padding, points[i].y - padding };
			}
		}

		// Clamp the padded points to the bounds of the screen
		if (paddedPoint.x < 2)
			paddedPoint.x = 2;
		if (paddedPoint.x > 1598)
			paddedPoint.x = 1598;
		if (paddedPoint.y < 2)
			paddedPoint.y = 2;
		if (paddedPoint.y > 898)
			paddedPoint.y = 898;

		paddedPoints.push_back(paddedPoint);
	}

	// Make the edges that will be drawn as the lines of the obstacles
	std::vector <std::pair<Vector2, Vector2>> edges;
	for (int i = 0; i < points.size(); i++)
	{
		int j = i + 1;
		if (j >= points.size())
		{
			std::pair<Vector2, Vector2> edge = { points[i], points.front() };
			edges.push_back(edge);
		}
		else
		{
			std::pair<Vector2, Vector2> edge = { points[i], points[j] };
			edges.push_back(edge);
		}
	}

	Obstacle o = { points, edges, padding };

	m_obstacles.push_back(o);

	m_polygons.push_back({});
	// Add the shape to the polygons that are going to be triangulated around to base the NavMesh on
	for (int i = 0; i < paddedPoints.size(); i++)
	{
		m_polygons.back().push_back(new p2t::Point(paddedPoints[i].x, paddedPoints[i].y));
	}
	// "Cut the hole" in the sheet of the NavMesh
	m_cdt->AddHole(m_polygons.back());

	return true;
}

void NavMesh::MakeMaze()
{
	// Vectorception. Will contain all the points of the multiple obstacles to be added to make the maze.
	std::vector<std::vector<Vector2>> vectors;
	std::vector<Vector2> v1 =
	{
		{1599, 1},
		{1, 1},
		{1, 899},
		{1340, 899},
		{1340, 640},
		{1450, 640},
		{1450, 800},
		{1460, 800},
		{1460, 630},
		{1330, 630},
		{1330, 890},
		{1050, 890},
		{1050, 770},
		{1040, 770},
		{1040, 890},
		{250, 890},
		{250, 780},
		{900, 780},
		{900, 770},
		{240, 770},
		{240, 890},
		{10, 890},
		{10, 10},
		{350, 10},
		{350, 260},
		{130, 260},
		{130, 270},
		{350, 270},
		{350, 590},
		{130, 590},
		{130, 600},
		{360, 600},
		{360, 400},
		{470, 400},
		{470, 600},
		{480, 600},
		{480, 390},
		{360, 390},
		{360, 10},
		{1120, 10},
		{1120, 300},
		{1130, 300},
		{1130, 10},
		{1590, 10},
		{1590, 899},
		{1599, 899}
	};
	std::vector<Vector2> v2 =
	{
		{750,400},
		{600,400},
		{600,630},
		{1000,630},
		{1000,500},
		{1150,500},
		{1150,490},
		{1000,490},
		{1000,400},
		{850,400},
		{850,410},
		{990,410},
		{990,620},
		{610,620},
		{610,410},
		{750,410}
	};
	std::vector<Vector2> v3 =
	{
		{850,150},
		{600,150},
		{600,300},
		{1000,300},
		{1000,150},
		{990,150},
		{990,290},
		{610,290},
		{610,160},
		{850,160}
	};
	std::vector<Vector2> v4 =
	{
		{1330,150},
		{1320,150},
		{1320,360},
		{1160,360},
		{1160,370},
		{1320,370},
		{1320,500},
		{1330,500},
		{1330,250},
		{1470,250},
		{1470,240},
		{1330,240}
	};
	std::vector<Vector2> v5 =
	{
		{1170,550},
		{1160,550},
		{1160,700},
		{900,700},
		{900,710},
		{1160,710},
		{1160,800},
		{1170,800}
	};
	vectors.push_back(v1);
	vectors.push_back(v2);
	vectors.push_back(v3);
	vectors.push_back(v4);
	vectors.push_back(v5);


	for (std::vector<Vector2> vector : vectors)
	{
		AddObstacle(vector, 10);
	}
}

void NavMesh::Build()
{
	// Takes all the polygons pushed to m_polygons and triangulates from all the vertices within.
	m_cdt->Triangulate();

	// first convert triangles to Nodes
	std::vector<p2t::Triangle*> triangles = m_cdt->GetTriangles();
	int i = 0;
	for (auto tri : triangles)
	{
		i++;
		auto node = new Node();

		node->vertices.push_back({ (float)tri->GetPoint(0)->x, (float)tri->GetPoint(0)->y });
		node->vertices.push_back({ (float)tri->GetPoint(1)->x, (float)tri->GetPoint(1)->y });
		node->vertices.push_back({ (float)tri->GetPoint(2)->x, (float)tri->GetPoint(2)->y });

		node->position.x = (node->vertices[0].x + node->vertices[1].x + node->vertices[2].x) / 3;
		node->position.y = (node->vertices[0].y + node->vertices[1].y + node->vertices[2].y) / 3;
		// For debug purposes
		node->tracker = i;
		// Constrains the nodes to within the bounds of the outer maze wall.
		if (node->position.x >= 10 && node->position.y >= 10 && node->position.x <= GetScreenWidth() - 10 && node->position.y <= GetScreenHeight() - 10)
		{
			m_nodes.push_back(node);
		}
		else
		{
			i--;
		}
	}

	// then link nodes that share triangle edges
	for (auto n : m_nodes)
	{
		for (auto n2 : m_nodes)
		{
			if (n == n2)
			{
				continue;
			}
			glm::vec2 v[2];
			if (n->GetAdjacentVertices(n2, v) == 2)
			{
				float mag = (n->position.x - n2->position.x) *
					(n->position.x - n2->position.x) +
					(n->position.y - n2->position.y) *
					(n->position.y - n2->position.y);

				float distance = glm::length(n->position - n2->position);
				n->connections.push_back(Edge(n2, distance));
				n2->connections.push_back(Edge(n, distance));
			}
		}
	}
	// cleanup polygons
	for (auto& p : m_polygons)
	{
		for (auto ptr : p)
		{
			delete ptr;
		}
	}
	m_polygons.clear();

	// close up Poly2Tri
	delete m_cdt;
	m_cdt = nullptr;
}

void NavMesh::Draw(bool connections)
{
	Color lineColor = DARKGREEN;
	Color obstacleColor = DARKBROWN;

	// draw nav mesh polygons, lair and exit AABBs for debugging
	if (connections)
	{
		for (int i = 0; i < m_nodes.size(); i++)
		{
			auto node = m_nodes[i];
			DrawLineEx(Utilities::ConvertVector(node->vertices[0]), Utilities::ConvertVector(node->vertices[1]), 2, lineColor);
			DrawLineEx(Utilities::ConvertVector(node->vertices[1]), Utilities::ConvertVector(node->vertices[2]), 2, lineColor);
			DrawLineEx(Utilities::ConvertVector(node->vertices[2]), Utilities::ConvertVector(node->vertices[0]), 2, lineColor);
			//DrawText(FormatText("% i", node->tracker), node->position.x, node->position.y, 15, RED);
			DrawCircle(node->position.x, node->position.y, 3, RED);
		}
			/*DrawRectangle(m_lair.x, m_lair.y, m_lair.width, m_lair.height, RED);
			DrawRectangle(m_exit.x, m_exit.y, m_exit.width, m_exit.height, RED);*/
	}
	// draw obstacles
	for (auto& o : m_obstacles)
	{
		o.Draw(obstacleColor);
	}
}

glm::vec2 NavMesh::GetRandomPosition()
{
	glm::vec2 pos;
	bool safe = false;
	do {
		// Will make sure that the random point that is looked for is within a node that can be traversed to
		float x = Utilities::Random(10, GetScreenWidth() - 10);
		float y = Utilities::Random(10, GetScreenHeight() - 10);
		pos = { x, y };
		bool inSafe;
		for (Node* n : m_nodes)
		{
			inSafe = PointInTri(&pos, &n->vertices[0], &n->vertices[1], &n->vertices[2]);
			if (inSafe)
			{
				return pos;
			}
		}
	} while (safe == false);
}

Node* NavMesh::FindClosest(float x, float y) const
{
	Node* closest = nullptr;
	float closestDist = 2000 * 2000;

	for (auto node : m_nodes)
	{
		float dist = (node->position.x - x) * (node->position.x - x) + (node->position.y - y) * (node->position.y - y);

		if (dist < closestDist)
		{
			closest = node;
			closestDist = dist;
		}
	}
	return closest;
}

float NavMesh::TriArea(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
{
	return ((v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y)) / 2.0);
}

// For making sure that a point is on a certain side of a 
int NavMesh::PointOrientation(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
{
	glm::vec2 ab = { v2.x - v1.x, v2.y - v1.y };
	glm::vec2 ac = { v3.x - v1.x, v3.y - v1.y };

	float cross = ab.x * ac.y - ab.y * ac.x;
	if (cross > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// For checking if a point is contained within a triangle by checking that the point is all on the same side
// of its three edges
bool NavMesh::PointInTri(const glm::vec2* pt, const glm::vec2* v1, const glm::vec2* v2, const glm::vec2* v3)
{
	int turns = PointOrientation(*v1, *v2, *pt) + PointOrientation(*v2, *v3, *pt) + PointOrientation(*v3, *v1, *pt);

	if (turns == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Find the node that the point is sitting in. 
Node* NavMesh::GetNode(glm::vec2 position)
{
	for (Node* n : m_nodes)
	{
		bool inNode = PointInTri(&position, &n->vertices[0], &n->vertices[1], &n->vertices[2]);
		if (inNode)
		{
			return n;
		}
	}
	return nullptr;
}

// For finding whether Obstacles are blocking line of sight from an agent to a target
bool NavMesh::LineIntersectsObstacle(glm::vec2 pos, glm::vec2 targetPos)
{
	for (Obstacle o : m_obstacles)
	{
		for (std::pair<Vector2, Vector2> e : o.m_edges)
		{
			glm::vec2 v1 = pos - glm::vec2{ e.first.x, e.first.y };
			glm::vec2 v2 = { e.second.x - e.first.x, e.second.y - e.first.y };
			glm::vec2 v3 = targetPos - pos;
			v3 = { -v3.y, v3.x };


			float dot = glm::dot(v2, v3);
			if (abs(dot) < 0.000001)
			{
				continue;
			}

			float t = (v1.y * v2.x - v1.x * v2.y) / dot;
			float s = glm::dot(v1, v3) / dot;

			if ((t >= 0.0 && t <= 1.0) && (s >= 0.0 && s <= 1.0))
			{
				return true;
			}
		}
	}
			return false;
}

float NavMesh::triarea2(glm::vec2 a, glm::vec2 b, glm::vec2 c)
{
	//Calculate the area of a triangle
	float ax = b.x - a.x;
	float ay = b.y - a.y;
	float bx = c.x - a.x;
	float by = c.y - a.y;
	return bx * ay - ax * by;
}

bool NavMesh::vequal(glm::vec2 a, glm::vec2 b)
{
	// Account for floating point error
	static const float eq = 0.001f * 0.001f;
	return glm::distance(a, b) < eq;
}

int NavMesh::stringPull(glm::vec2* portals, int nportals, std::vector<glm::vec2>& pts)
{
	// Find straight path.
	int npts = 0;
	// Init scan state
	glm::vec2 portalApex, portalLeft, portalRight;
	int apexIndex = 0, leftIndex = 0, rightIndex = 0;
	portalApex = portals[0];
	portalLeft = portals[0];
	portalRight = portals[1];

	// Add start point.
	pts.push_back(portalApex);
	npts++;

	for (int i = 1; i < nportals; ++i)
	{
		glm::vec2 left = portals[i * 2];
		glm::vec2 right = portals[i * 2 + 1];

		// Update right vertex.
		if (triarea2(portalApex, portalRight, right) <= 0.0f)
		{
			if (vequal(portalApex, portalRight) || triarea2(portalApex, portalLeft, right) > 0.0f)
			{
				// Tighten the funnel.
				portalRight = right;
				rightIndex = i;
			}
			else
			{// Use portal left and portal right to asjust the point added to the path
				// Right over left, insert left to path and restart scan from portal left point.
				pts.push_back(portalLeft);
				npts++;
				// Make current left the new apex.
				portalApex = portalLeft;
				apexIndex = leftIndex;
				// Reset portal
				portalLeft = portalApex;
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;
				// Restart scan
				i = apexIndex;
				continue;
			}
		}

		// Update left vertex.
		if (triarea2(portalApex, portalLeft, left) >= 0.0f)
		{
			if (vequal(portalApex, portalLeft) || triarea2(portalApex, portalRight, left) < 0.0f)
			{
				// Tighten the funnel.
				portalLeft = left;
				leftIndex = i;
			}
			else
			{
				// Left over right, insert right to path and restart scan from portal right point.
				pts.push_back(portalRight);
				npts++;
				// Make current right the new apex.
				portalApex = portalRight;
				apexIndex = rightIndex;
				// Reset portal
				portalLeft = portalApex;
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;
				// Restart scan
				i = apexIndex;
				continue;
			}
		}
	}
	// Append last point to path.

	pts.push_back(portals[(nportals - 1) * 2]);
	npts++;


	return npts;
}

std::vector<glm::vec2> NavMesh::SmoothPath(glm::vec2 start, glm::vec2 end, const std::vector<Node*>& path, std::vector<glm::vec2>& smoothPath)
{
	if (path.size() == 0)
	{
		return std::vector<glm::vec2>();
	}
	smoothPath.clear();
	glm::vec2* portals = new glm::vec2[(path.size() + 1) * 2];
	int index = 0;

	// add start to portals	
	portals[index++] = start;
	portals[index++] = start;

	Node* prev = nullptr;
	for (auto n : path)
	{
		Node* node = n;
		if (prev != nullptr)
		{
			glm::vec2 adj[2];
			prev->GetAdjacentVertices(node, adj);
			glm::vec2 fromPrev = { node->position.x - prev->position.x, node->position.y - prev->position.y };
			glm::vec2 toAdj0 = { adj[0].x - prev->position.x, adj[0].y - prev->position.y };
			if ((fromPrev.x * toAdj0.y - toAdj0.x * fromPrev.y) > 0)
			{
				portals[index++] = adj[0];
				portals[index++] = adj[1];
			}
			else
			{
				portals[index++] = adj[1];
				portals[index++] = adj[0];
			}
		}
		prev = node;
	}

	// add end to portals	
	portals[index++] = end;
	portals[index++] = end;

	// shorten path through portals
	int count = stringPull(portals, index / 2, smoothPath);

	delete[] portals;

	return smoothPath;
}

