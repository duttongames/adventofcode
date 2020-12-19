#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <bitset>

using namespace std;

long startingNumbers[6] = { 1,0,15,2,10,13 };
vector<long> numbers;
unordered_map<long, long> lastNumbers;

long GetLastNumber(long lastNumber)
{
	numbers.clear();
	lastNumbers.clear();

	for (long i = 0; i < lastNumber; i++)
	{
		//Start with the starting numbers.
		if (i < sizeof(startingNumbers) / sizeof(startingNumbers[0]))
		{
			numbers.push_back(startingNumbers[i]);
			lastNumbers[startingNumbers[i]] = i + 1;
		}

		else
		{
			bool newNumber = true;

			//If the number has not been said before...
			if (lastNumbers.count(numbers[i - 1]) <= 0)
			{
				//Push 0 to the numbers list.
				numbers.push_back(0);
				lastNumbers[numbers[i - 1]] = i;
			}

			//If the number has been said before...
			else
			{
				numbers.push_back(i - lastNumbers[numbers[i - 1]]);
				lastNumbers[numbers[i - 1]] = i;
			}

			//Return the last number.
			if (i == lastNumber - 1)
			{
				return numbers[numbers.size() - 1];
			}
		}
	}

	return 0;
}