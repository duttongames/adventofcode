#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<long long> xmasNumbers;

//Gets the first number in the list that does not follow the pattern of being a sum of the 25 numbers before it.
long long GetInvalidNumber()
{
	string line;

	ifstream xmas("Xmas.txt");

	xmasNumbers.clear();

	while (getline(xmas, line))
	{
		xmasNumbers.push_back(stoll(line));
	}

	for (int i = 25; i < xmasNumbers.size(); i++)
	{
		for (int j = 0; j < i - 1; j++)
		{
			for (int k = 1; k < i; k++)
			{
				if (xmasNumbers[j] + xmasNumbers[k] == xmasNumbers[i])
				{
					j = i - 1;
					k = i;
				}
			}

			if (j == i - 2)
			{
				return xmasNumbers[i];
			}
		}
	}

	return 0;
}

//Finds a contiguous set of numbers which add together to get the invalid number and returns the
//sum of the smallest and largest numbers in this range.
long long GetEncryptionWeakness(int invalidNumber)
{
	vector<long long> encryptionNumbers;

	for (int i = 0; i < xmasNumbers.size(); i++)
	{
		long long total = 0;
		encryptionNumbers.clear();

		for (int j = i; j < xmasNumbers.size(); j++)
		{
			total += xmasNumbers[j];
			encryptionNumbers.push_back(xmasNumbers[j]);

			if (total > invalidNumber)
			{
				j = xmasNumbers.size();
			}

			if (total == invalidNumber)
			{
				i = xmasNumbers.size();
				j = xmasNumbers.size();
			}
		}
	}

	long long min = 900000000000000;
	int max = 0;

	for (int i = 0; i < encryptionNumbers.size(); i++)
	{
		if (encryptionNumbers[i] < min)
		{
			min = encryptionNumbers[i];
		}

		if (encryptionNumbers[i] > max)
		{
			max = encryptionNumbers[i];
		}
	}

	return min + max;
}