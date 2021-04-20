#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> memoryBlocks = { 4,	1, 15, 12, 0, 9, 9,	5, 5, 8, 7,	3, 14, 5, 12, 3 };

//Reallocates memory until a configuration that has been seen before occurs, then returns the number of cycles taken.
int DetermineDupeConfig()
{
	vector<int> currentConfig = memoryBlocks;
	map<vector<int>, int> configurations;

	int cycles = 0;

	bool duplicate = false;

	while (!duplicate)
	{
		//Finds the bank with the most blocks.
		int mostBlocks = 0;
		int index = 0;

		for (int i = 0; i < currentConfig.size(); ++i)
		{
			if (currentConfig[i] > mostBlocks)
			{
				mostBlocks = currentConfig[i];
				index = i;
			}
		}

		//Reallocate memory.
		currentConfig[index] = 0;

		while (mostBlocks > 0)
		{
			if (index < currentConfig.size() - 1)
			{
				index++;
			}

			else
			{
				index = 0;
			}

			currentConfig[index]++;
			mostBlocks--;
		}

		cycles++;

		//If the configuration has appeared more than once, there is a duplicate configuration.
		if (configurations[currentConfig] > 0)
		{
			duplicate = true;
		}

		//Store the current cycles.
		else
		{
			configurations[currentConfig] = cycles;
		}
	}
	
	//Output the cycles between the duplicates.
	cout << "The amount of cycles between the first and second configuration occurence is: " + to_string(cycles - configurations[currentConfig]) << endl;

	return cycles;
}