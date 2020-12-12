#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> adapters;

//Gets the first number in the list that does not follow the pattern of being a sum of the 25 numbers before it.
int GetJoltDifferences()
{
	string line;

	ifstream listOfAdapters("JoltageAdapters.txt");

	adapters.clear();

	while (getline(listOfAdapters, line))
	{
		adapters.push_back(stoi(line));
	}

	bool sorted = false;

	while (sorted == false)
	{
		sorted = true;

		for (int i = 1; i < adapters.size(); i++)
		{
			if (adapters[i] < adapters[i - 1])
			{
				int temp = adapters[i];
				adapters[i] = adapters[i - 1];
				adapters[i - 1] = temp;
				sorted = false;
			}
		}
	}

	int oneJoltDifferences = 0;
	int threeJoltDifferences = 0;

	//Account for the charging outlet being 0 jolts and the final adapter being 3 jolts higher than the highest.
	if (adapters[0] == 1)
	{
		oneJoltDifferences++;
	}

	else if (adapters[0] == 3)
	{
		threeJoltDifferences++;
	}

	threeJoltDifferences++;

	for (int i = 1; i < adapters.size(); i++)
	{
		if (adapters[i] - adapters[i - 1] == 3)
		{
			threeJoltDifferences++;
		}

		if (adapters[i] - adapters[i - 1] == 1)
		{
			oneJoltDifferences++;
		}
	}

	return oneJoltDifferences * threeJoltDifferences;
}

//Gets the total amount of adapter combinations.
long long GetTotalCombinations()
{
	long long combinations = 0;

	adapters.insert(adapters.begin(), 0);
	adapters.push_back(adapters[adapters.size() - 1] + 3);

	/*CREDIT TO GAMEPOPPER ON REDDIT FOR THIS SOLUTION*/
	std::vector<long long> path(adapters.size(), 0);
	path[path.size() - 1] = 1;
	for (int i = path.size() - 1; i >= 0; i--)
	{
		for (int j = i + 1; j < adapters.size(); j++)
		{
			if (adapters[j] - adapters[i] <= 3)
			{
				path[i] += path[j];
			}

			else
			{
				break;
			}
		}
	}

	combinations = path[0];
	/*CREDIT TO GAMEPOPPER ON REDDIT FOR THIS SOLUTION*/

	return combinations;
}