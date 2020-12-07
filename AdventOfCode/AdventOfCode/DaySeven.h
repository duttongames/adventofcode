#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Finds the amount of bags that contain the specified colour.
int FindBagsThatContain(string colourToCount)
{
	string line;

	ifstream rules("LuggageRules.txt");

	map<string, vector<string>> luggageColours;

	string colour = "";
	string firstColour = "";
	vector<string> containedColours;
	int spaceCount = 0;
	bool startContainedColours = false;

	//Loop through the lines of the txt.
	while (getline(rules, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ' || line[i] == ',')
			{
				spaceCount++;

				if (firstColour == "" && spaceCount == 2)
				{
					firstColour = colour;
					colour = "";
					spaceCount = 0;
				}

				if (startContainedColours && spaceCount == 2)
				{
					colour = colour.substr(1, colour.size());
					containedColours.push_back(colour);
					colour = "";
					spaceCount = 0;
					startContainedColours = false;
				}

				else if (spaceCount == 3)
				{
					colour = "";
					spaceCount = 0;
					startContainedColours = true;
				}
			}
				
			colour += line[i];
		}

		luggageColours.insert(pair<string, vector<string>>(firstColour, containedColours));
		startContainedColours = false;
		containedColours.clear();
		firstColour = "";
		colour = "";
		spaceCount = 0;
	}

	int goldCount = 0;
	vector<string> checkedBags;
	vector<string> bagsContainingGold;
	bagsContainingGold.push_back(colourToCount);

	int foundBags = 1;

	while (foundBags > 0)
	{
		foundBags = 0;

		vector<string> bagsToCheck = bagsContainingGold;
		bagsContainingGold.clear();

		for (map<string, vector<string>>::iterator it = luggageColours.begin(); it != luggageColours.end(); it++)
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				for (int j = 0; j < bagsToCheck.size(); j++)
				{
					if (it->second[i] == bagsToCheck[j] && find(checkedBags.begin(), checkedBags.end(), it->first) == checkedBags.end())
					{
						checkedBags.push_back(it->first);
						bagsContainingGold.push_back(it->first);
						goldCount++;
						foundBags++;
					}
				}
			}
		}
	}

	return goldCount;
}

//Counts the total amount of bags that a specified bag contains.
int CountBags(string colourToCount, int &bags, int amountOfBags)
{
	string line;
	string word = "";
	bool foundBag = false;

	map<string, int> bagsToCheck;

	ifstream rules("LuggageRules.txt");

	//Loop through the lines of the txt.
	while (getline(rules, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (word == colourToCount)
			{
				foundBag = true;
				word = "";
			}

			if (foundBag)
			{
				string currentChar = "";
				currentChar += line[i];

				if (currentChar.find_first_not_of("0123456789") != string::npos && word.find_first_of("0123456789") == string::npos)
				{
					word = "";
				}

				if (line[i] == ',' || line[i] == '.')
				{
					if (word.size() > 1)
					{
						int number = stoi(word.substr(1, 2));

						if (word[word.size() - 1] == 's')
						{
							word = word.substr(3, word.size() - 8);
						}

						else
						{
							word = word.substr(3, word.size() - 7);
						}

						bagsToCheck.insert(pair<string, int>(word, number));
						word = "";
					}
				}
			}

			word += line[i];
		}

		foundBag = false;
		word = "";
	}

	for (map<string, int>::iterator it = bagsToCheck.begin(); it != bagsToCheck.end(); it++)
	{
		bags += it->second * amountOfBags;
		CountBags(it->first, bags, it->second * amountOfBags);
	}

	return bags;
}