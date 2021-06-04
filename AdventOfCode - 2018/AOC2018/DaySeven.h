#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<char, vector<char>> steps;
vector<char> stepsLeft;

//Reads the steps for assembling the Sleigh.
void ReadSteps()
{
	ifstream stepsFile("Steps.txt");
	string line;

	//Read and save the steps that need to be finished for each step to begin.
	while (getline(stepsFile, line))
	{
		steps[line[36]].push_back(line[5]);

		if (steps.find(line[5]) == steps.end())
		{
			vector<char> emptyVec;
			steps[line[5]] = emptyVec;
		}
	}

	//Loop through the map of steps and add them to the stepsLeft list.
	map<char, vector<char>>::iterator stepIter;

	for (stepIter = steps.begin(); stepIter != steps.end(); stepIter++)
	{
		stepsLeft.push_back(stepIter->first);
	}
}

//Determine the order of the steps and return it as a string.
string DetermineOrder()
{
	string order = "";

	//Loop until there are no steps left.
	while (stepsLeft.size() > 0)
	{
		char nextStep = ' ';

		//Loop through the map of steps.
		map<char, vector<char>>::iterator stepIter;

		vector<char> possibleNextSteps;

		for (stepIter = steps.begin(); stepIter != steps.end(); stepIter++)
		{
			//Determine the possible next steps and add them to the list.
			if (stepIter->second.size() == 0)
			{
				possibleNextSteps.push_back(stepIter->first);
			}
		}

		nextStep = possibleNextSteps[0];

		//Take the next alphabetic step.
		for (int i = 1; i < possibleNextSteps.size(); ++i)
		{
			if (possibleNextSteps[i] < nextStep)
			{
				nextStep = possibleNextSteps[i];
			}
		}

		//Remove the next step from the list as it is completed.
		for (int i = 0; i < stepsLeft.size(); ++i)
		{
			if (stepsLeft[i] == nextStep)
			{
				stepsLeft.erase(stepsLeft.begin() + i);
				steps.erase(nextStep);
				break;
			}
		}

		//Remove the step that has been completed from all the other steps.
		for (stepIter = steps.begin(); stepIter != steps.end(); stepIter++)
		{
			for (int i = 0; i < stepIter->second.size(); ++i)
			{
				if (stepIter->second[i] == nextStep)
				{
					stepIter->second.erase(stepIter->second.begin() + i);
				}
			}
		}

		order += nextStep;
	}

	return order;
}