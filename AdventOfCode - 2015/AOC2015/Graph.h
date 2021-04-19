#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Node
{
	//The name of the Node.
	string nodeName;

	//Contains the Nodes and their respective weightings that this Node is connected to.
	map<Node*, int> connectedNodes;

	//Contains the distance value of the Node.
	int distance = INT_MAX;

	//The previous Node.
	Node* prevNode = nullptr;
};

class Graph
{
public:
	Graph();
	~Graph();

	//The Nodes that make up the Graph.
	map<string, Node*> nodes;

	//Adds a new Node to the Graph.
	void AddNode(string nodeName);
};