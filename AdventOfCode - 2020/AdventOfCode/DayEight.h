#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Gets the value of the accumulator once the program has been terminated.
int GetAccValue()
{
	string line;

	ifstream code("BootCode.txt");

	int acc = 0;

	vector<string> listOfInstructions;
	vector<int> instructionsExecuted;

	//Loop through the lines of the txt and add them to the list of instructions.
	while (getline(code, line))
	{
		listOfInstructions.push_back(line);
		instructionsExecuted.push_back(0);
	}

	for (int j = 0; j < listOfInstructions.size(); j++)
	{
		bool changeBack = false;
		bool reachedEnd = true;

		if (listOfInstructions[j].substr(0, 3) == "jmp")
		{
			listOfInstructions[j] = "nop" + listOfInstructions[j].substr(3, listOfInstructions[j].size());
			changeBack = true;
		}

		acc = 0;
		vector<int> executed = instructionsExecuted;

		for (int i = 0; i < listOfInstructions.size(); i++)
		{
			if (executed[i] > 0)
			{
				i = listOfInstructions.size() - 1;
				reachedEnd = false;
			}

			executed[i]++;

			if (listOfInstructions[i].substr(0, 3) == "acc")
			{
				if (listOfInstructions[i].substr(4, 1) == "+")
				{
					acc += stoi(listOfInstructions[i].substr(5, listOfInstructions[i].size()));
				}

				else if (listOfInstructions[i].substr(4, 1) == "-")
				{
					acc -= stoi(listOfInstructions[i].substr(5, listOfInstructions[i].size()));
				}
			}

			if (listOfInstructions[i].substr(0, 3) == "jmp")
			{
				if (listOfInstructions[i].substr(4, 1) == "+")
				{
					if (i + stoi(listOfInstructions[i].substr(5, listOfInstructions[i].size())) < listOfInstructions.size())
					{
						i += stoi(listOfInstructions[i].substr(5, listOfInstructions[i].size())) - 1;
					}
				}

				else if (listOfInstructions[i].substr(4, 1) == "-")
				{
					if (i - stoi(listOfInstructions[i].substr(5, listOfInstructions[i].size())) > 0)
					{
						i -= stoi(listOfInstructions[i].substr(5, listOfInstructions[i].size())) + 1;
					}
				}
			}

			if (i == listOfInstructions.size() - 1 && reachedEnd)
			{
				return acc;
			}
		}

		if (changeBack)
		{
			listOfInstructions[j] = "jmp" + listOfInstructions[j].substr(3, listOfInstructions.size());
			changeBack = false;
		}
	}

	return acc;
}
