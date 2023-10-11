#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::OnCreate(std::vector<Node*> nodes_)
{
	// given a list of nodes, initialize a matrix of costs with 0.0 
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		// populate the internal map
		if (i != nodes_[i]->getLabel())
		{
			std::cerr << "node with label 'i' not in the 'i' position for " << i << std::endl;
			return false;
		}

		node[i] = nodes_[i];

		// set up connections
		cost[i].resize(numNodes);

		for (int j = 0; j < numNodes; j++)
		{
			//initialize connection
			cost[i][j] = 0.0f;
		}
	}

	return true;
}

int Graph::numNodes()
{
	return node.size();
}

void Graph::addWeightedConnection(int fromNode, int toNode, float weight)
{
	cost[fromNode][toNode] = weight;
}

std::vector<int> Graph::neighbours(int fromNode)
{
	std::vector<int> result = {};
	for (int j = 0; j < numNodes(); j++)
	{
		if (cost[fromNode][j] > 0.0f)
		{
			result.push_back(j);
		}
	}
	return result;
}

std::vector<int> Graph::Dijkstra(int start, int goal)
{
	return {};
}
