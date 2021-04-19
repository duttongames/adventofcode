#include "Graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{
	map<string, Node*>::iterator nodeIter;

	for (nodeIter = nodes.begin(); nodeIter != nodes.end(); ++nodeIter)
	{
		delete nodeIter->second;
	}
}

void Graph::AddNode(string nodeName)
{
	Node* newNode = new Node();
	newNode->nodeName = nodeName;
	nodes[nodeName] = newNode;
}