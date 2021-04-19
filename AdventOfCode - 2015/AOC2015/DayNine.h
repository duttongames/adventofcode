#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>

#include "Graph.h"

using namespace std;

Graph* locationGraph;

//Creates the Graph for determining the shortest route.
void CreateGraph()
{
	locationGraph = new Graph();
	
	ifstream routeFile("Routes.txt");
	string line;

	//Loop through each route and add them to the graph.
	while (getline(routeFile, line))
	{
		int wordNumber = 0;
		string currentWord;

		string firstLocation = "";
		string secondLocation = "";

		int distance = 0;

		//Loop through each character of the line.
		for (int i = 0; i < line.size(); ++i)
		{
			//Add the individual characters of the locations and distance.
			if (wordNumber == 0 || wordNumber == 2 || wordNumber == 4)
			{
				currentWord += line[i];
			}

			//Determine the values of the locations and distance and store them in variables.
			if (line[i] == ' ' || i == line.size() - 1)
			{
				switch (wordNumber)
				{
					case 0:
						firstLocation = currentWord;
						break;

					case 2:
						secondLocation = currentWord;
						break;

					case 4:
						distance = stoi(currentWord);
						break;
				}

				currentWord = "";
				wordNumber++;
			}
		}

		//Add the locations to the Graph as Node if they are not already in the Graph.
		if (locationGraph->nodes[firstLocation] == nullptr)
		{
			locationGraph->AddNode(firstLocation);
		}

		if (locationGraph->nodes[secondLocation] == nullptr)
		{
			locationGraph->AddNode(secondLocation);
		}

		//Add the edge and weighting between the two locations.
		locationGraph->nodes[firstLocation]->connectedNodes[locationGraph->nodes[secondLocation]] = distance;
		locationGraph->nodes[secondLocation]->connectedNodes[locationGraph->nodes[firstLocation]] = distance;
	}
}

//Uses the Dijkstra Algorithm to find the shortest path from one Node to another.
int Dijkstra(Node* startingNode)
{
	map<string, Node*>::iterator nodeIter;

	vector<Node*> graphNodes;

	for (nodeIter = locationGraph->nodes.begin(); nodeIter != locationGraph->nodes.end(); nodeIter++)
	{
		nodeIter->second->distance = INT_MAX;
		nodeIter->second->prevNode = nullptr;
		graphNodes.push_back(nodeIter->second);
	}

	cout << startingNode->nodeName << endl;

	startingNode->distance = 0;

	Node* currentNode = startingNode;

	int totalDistance = 0;

	while (graphNodes.size() > 0)
	{
		int smallestDistance = INT_MAX;

		for (int i = 0; i < graphNodes.size(); ++i)
		{
			if (graphNodes[i]->distance < smallestDistance)
			{
				smallestDistance = graphNodes[i]->distance;
				currentNode = graphNodes[i];
			}
		}

		graphNodes.erase(std::remove(graphNodes.begin(), graphNodes.end(), currentNode), graphNodes.end());

		map<Node*, int>::iterator connectIter;

		int alt = 0;

		for (connectIter = currentNode->connectedNodes.begin(); connectIter != currentNode->connectedNodes.end(); connectIter++)
		{
			alt = currentNode->distance + connectIter->second;

			if (alt < connectIter->first->distance)
			{
				connectIter->first->distance = alt;
				connectIter->first->prevNode = currentNode;
			}
		}

		totalDistance += currentNode->distance;
	}

	return totalDistance;
}

//Gets the distance of the shortest route to visit each location.
int GetShortestDistance()
{
	CreateGraph();

	map<string, Node*>::iterator graphIter;

	int shortestDistance = INT_MAX;

	for (graphIter = locationGraph->nodes.begin(); graphIter != locationGraph->nodes.end(); ++graphIter)
	{
		int nextDistance = Dijkstra(graphIter->second);

		cout << nextDistance << endl << endl;

		if (nextDistance < shortestDistance)
		{
			shortestDistance = nextDistance;
		}
	}

	delete locationGraph;
	return shortestDistance;
}