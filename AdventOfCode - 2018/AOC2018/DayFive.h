#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string polymer;
char units[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

//Reads the polymer from the file and saves it to the polymer string.
void ReadPolymer()
{
	ifstream polymerFile("Polymer.txt");
	string line;

	//Read and save the polymer to a string.
	while (getline(polymerFile, line))
	{
		polymer += line;
	}
}

//Reacts a Polymer and returns the number of units remaining.
int ReactPolymer(string polymerToReact)
{
	string polymerCopy = polymerToReact;

	//Loop through each unit of the polymer.
	for (int i = 1; i < polymerCopy.size(); ++i)
	{
		//Check if the units have the same type but opposite polarity.
		if (polymerCopy[i - 1] == polymerCopy[i] - 32 || polymerCopy[i - 1] == polymerCopy[i] + 32)
		{
			//Remove the two polymers.
			polymerCopy.erase(i - 1, 2);

			//Go back 2.
			i -= 2;

			if (i < 0)
			{
				i++;
			}
		}
	}

	return polymerCopy.size();
}

//Finds the unit that is causing the most problems and returns the length of the polymer after
//removing all instances of that unit and reacting the polymer.
int FindProblemUnit()
{
	int shortestPolymer = INT_MAX;

	//Loop through all the unit types.
	for (int i = 0; i < 26; ++i)
	{
		string nextPolymer = polymer;

		//Erase all occurences of a unit type from the next polymer to test.
		nextPolymer.erase(std::remove(nextPolymer.begin(), nextPolymer.end(), units[i]), nextPolymer.end());
		nextPolymer.erase(std::remove(nextPolymer.begin(), nextPolymer.end(), units[i] - 32), nextPolymer.end());

		//Fully react the polymer.
		int polymerLength = ReactPolymer(nextPolymer);

		//If the length of the reacted polymer is the shortest polymer so far, save its length.
		if (polymerLength < shortestPolymer)
		{
			shortestPolymer = polymerLength;
		}
	}

	return shortestPolymer;
}