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

// might be better to put these structs in private area of Graph.h

struct NodeAndPriority
{
	// member variables
	Node* node;
	float priority;

	// constructors
	// We'll use the "universal" constructor when needed.
	// See: https://learn.microsoft.com/en-us/cpp/cpp/initializing-classes-and-structs-without-constructors-cpp?view=msvc-170

	// useful functions
	void print()
	{
		printf("Node: %i, priority: %.2f \n", node->getLabel(), priority);
	}

	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		// make it a min queue: lowest value of priority at top of the queue
		return lhs.priority > rhs.priority;
	}
};

std::vector<int> Graph::Dijkstra(int start, int goal)
{
	float new_cost;
	float priority;
	Node* currentNode = node[start];
	int current = currentNode->getLabel(); // useful for index into came_from and cost_so_far

	std::priority_queue<NodeAndPriority, std::deque<NodeAndPriority>, NodeAndPriority > frontier;
	frontier.push( NodeAndPriority { currentNode, 0.0f } );

	//track solution path (n.b. integers are labels of the nodes)
	std::vector<int> came_from;
	came_from.resize(numNodes());

	//cost so far storage
	//use map, not vector, to allow detecting if a node has an entry
	std::map<int, float> cost_so_far;
	cost_so_far[start] = 0.0f;

	//implement algorithm

	// loop through frontier, while it not empty
	{
		// get the top node, AND pop it off
		// if its the goal, then break out

		// for the neighbours of current node
		{
			// calculate new cost
			// if you add heuristic(), then you've got A*
			// if neighbour is not an index in cost_so_far, or new cost is lower
			{
				// found a better path, so update data structures
			}
		}
	}

	// Follow the breadcrumbs in came_from to produce path
	std::vector<int> path = {};

	// do stuff to follow breadcrumbs

	return path;
}


