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

int PrintTribSequence(int currentNumber)
{
	vector<long long> dp(currentNumber);
	dp[0] = dp[1] = 0;
	dp[2] = 1;

	for (int i = 3; i < currentNumber; i++)
		dp[i] = dp[i - 1] +
		dp[i - 2] +
		dp[i - 3];

	for (int i = 0; i < dp.size(); i++)
	{
		cout << dp[i] << endl;
	}

	return 0;
}

//Gets the total amount of adapter combinations iteratively.
long long GetTotalCombinations()
{
	long long combinations = 0;

	for (int i = 0; i < adapters.size(); i++)
	{
		vector<int> currentCombination;

		for (int j = 0; j < adapters.size(); j++)
		{
			for (int k = 0; k < adapters.size(); k++)
			{
				if (adapters[j] - adapters[k] > 0 && adapters[j] - adapters[k] < 4)
				{
					currentCombination.push_back(adapters[k]);
				}
			}

			if (currentCombination.size() == adapters.size())
			{
				combinations++;
			}

			currentCombination.clear();
		}
	}

	cout << to_string(combinations) << endl;

	return combinations;
}