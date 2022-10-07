#include "Graph.h"

Graph::Graph(vector<Node*> nodes_)
{
	// given a list of nodes
	// initialize a matrix of costs
	// with 0.0 weights
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		// add the nodes to internal list
		node[i] = nodes_[i];

		//set up the connections
		cost[i].resize(numNodes);
		for (int j = 0; j < numNodes; j++)
		{
			//initialize connections
			cost[i][j] = 0.0f;
		}
	}
}

Graph::~Graph()
{}

int Graph::numNodes()
{
	return node.size();
	// return cost.size();
}

void Graph::addWeightConnection(
	int fromNode, int toNode, float weight
)
{
	cost[fromNode][toNode] = weight;
}

vector<int> Graph::neighbours(int fromNode)
{
	vector<int> result = {};
	for (int j = 0; j < numNodes(); j++)
	{
		if (cost[fromNode][j] > 0.0f)
		{
			result.push_back(j);
		}
	}
	return result;
}

vector<int> Graph::Dijkstra(
	int startNode, int goalNode
)
{
	return {};
}