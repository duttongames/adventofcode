#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//Identifies when the list of jumps goes out of range/finds the exit and returns the number of steps taken.
int FindExit(int offsetChangeMode)
{
	ifstream jumpFile("Jumps.txt");
	string line;

	vector<int> jumpList;
	
	//Loop through each jump and store it in the jump list.
	while (getline(jumpFile, line))
	{
		jumpList.push_back(stoi(line));
	}

	int steps = 0;
	int currentIndex = 0;

	//Go through the Jump List until an exit is found.
	while (currentIndex > -1 && currentIndex < jumpList.size())
	{
		int jumpValue = jumpList[currentIndex];

		//If the offset mode is 1, simply increment the jump value.
		if (offsetChangeMode == 1)
		{
			jumpList[currentIndex]++;
		}

		//If the offset mode is 2, increment the jump value only if the offset is less than 3, otherwise decrement it.
		else
		{
			if (jumpValue < 3)
			{
				jumpList[currentIndex]++;
			}

			else
			{
				jumpList[currentIndex]--;
			}
		}

		//Move to the next jump in the list.
		currentIndex = currentIndex + jumpValue;
		steps++;
	}

	//Return the number of steps taken to reach the exit.
	return steps;
}