#ifndef GRAPH_H
#define GRAPH_H

#include <vector> // from STL
#include <map>
#include "Node.h"
#include <iostream>
#include <queue>

using namespace std;

class Graph
{
private:
	// a list of the nodes
	//I could use STL vector, but map matches some textbooks
	map<int, Node*> node;
	// node[2]

	// a 2D matrix of the connection costs
	// (not efficient storage)
	vector< vector< float > > cost;
	
public:
	Graph();
	~Graph();
	bool OnCreate(vector< Node* > nodes_);
	int numNodes();
	Node* getNode(int label) { return node[label]; }
	void addWeightConnection(int fromNode, int toNode, float weight);
	vector<int> neighbours(int fromNode);
	vector<int> Dijkstra(int start, int goal);
};

#endif
