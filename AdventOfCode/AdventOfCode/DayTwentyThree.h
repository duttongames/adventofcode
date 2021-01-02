#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> cups = { 7, 1, 6, 8, 9, 2, 5, 4, 3 };
int currentCupPosition = 0;
int currentCup;

//Checks the status of the cups. Used for debugging.
void CheckStatus()
{
	for (int i = 0; i < cups.size(); i++)
	{
		cout << to_string(cups[i]) + ", ";
	}

	cout << endl;
}

//Returns the order of the cup labels once all moves have finished.
string GetFinalFormation()
{
	bool startRecording = false;
	string finalFormation;

	for (int i = 0; i < cups.size(); i++)
	{
		if (startRecording && cups[i] != 1)
		{
			finalFormation += to_string(cups[i]);
		}

		if (cups[i] == 1)
		{
			if (startRecording == false)
			{
				startRecording = true;
			}

			else
			{
				break;
			}
		}

		if (i == cups.size() - 1)
		{
			i = -1;
		}
	}

	return finalFormation;
}

//Perform a single move.
void Move()
{
	vector<int> pickedUpCups;
	int cupToSearchFor = cups[currentCupPosition] - 1;
	int currentCup = cups[currentCupPosition];
	bool cupFound = false;

	//Take out the three cups clockwise of the current cup.
	for (int i = 0; i < 3; i++)
	{
		int clockwiseNumber = currentCupPosition + 1;

		if (clockwiseNumber > cups.size() - 1)
		{
			clockwiseNumber = 0;
		}

		if (cups[clockwiseNumber] == cupToSearchFor)
		{
			cupToSearchFor--;

			if (cupToSearchFor < 1)
			{
				cupToSearchFor = 9;
			}
		}

		pickedUpCups.push_back(cups[clockwiseNumber]);

		if (clockwiseNumber == 0)
		{
			cups.erase(cups.begin(), cups.begin() + 1);
		}

		else
		{
			cups.erase(cups.begin() + currentCupPosition + 1, cups.begin() + currentCupPosition + 2);
		}
	}

	//Find the next destination cup.
	while (cupFound == false)
	{
		for (int i = 0; i < cups.size(); i++)
		{
			if (cups[i] == cupToSearchFor)
			{
				cups.insert(cups.begin() + i + 1, pickedUpCups[2]);
				cups.insert(cups.begin() + i + 1, pickedUpCups[1]);
				cups.insert(cups.begin() + i + 1, pickedUpCups[0]);
				cupFound = true;
				break;
			}
		}

		if (cupFound == false)
		{
			cupToSearchFor--;

			if (cupToSearchFor < 1)
			{
				cupToSearchFor = 9;
			}
		}
	}

	//Shift the cups until the current cup is in the correct position again.
	while (cups[currentCupPosition] != currentCup)
	{
		int temp = cups[cups.size() - 1];

		for (size_t i = cups.size() - 1; i > 0; i--)
		{
			cups.at(i) = cups.at(i - 1);
		}

		cups[0] = temp;
	}

	//Select the next cup, immediately clockwise of the current cup.
	if (currentCupPosition == 8)
	{
		currentCupPosition = 0;
	}

	else
	{
		currentCupPosition++;
	}

	pickedUpCups.clear();
}

//Simulates the given number of moves and returns the final cup formation.
string SimulateMoves(int moveAmount)
{
	string finalFormation;

	for (int i = 0; i < moveAmount; i++)
	{
		Move();
	}

	finalFormation = GetFinalFormation();
	return finalFormation;
}