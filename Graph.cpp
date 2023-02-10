#include "Graph.h"

Graph::Graph()
{

}

bool Graph::OnCreate(vector< Node* > nodes_)
{
	// given a list of nodes, initialize a matrix of costs with 0.0 weights
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		// add the nodes to internal list
		if (i != nodes_[i]->getLabel())
		{
			std::cerr << "node with label 'i' not in the 'i' position for " << i << endl;
			return false;
		}

		// nodes_[i]->label might not be i
		node[i] = nodes_[i];

		// set up the connections
		cost[i].resize(numNodes);

		for (int j = 0; j < numNodes; j++)
		{
			// initialize connection
			cost[i][j] = 0.0f;
		}

	}
	return true;
}

Graph::~Graph()
{
	// Node instances were created elsewhere,
	// so no memory cleanup of them!!!
	// Some other class is responsible for that
}

int Graph::numNodes()
{
	return node.size();
}

void Graph::addWeightConnection(int fromNode, int toNode, float weight)
{
	cost[fromNode][toNode] = weight;
	// [i,j] is wrong
	// [i][j] is correct
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

vector<int> Graph::Dijkstra(int start, int goal)
{
	return {};
}
