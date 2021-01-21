#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> boxIDs;

//Get the final resulting frequency after all the frequency changes.
int GetBoxChecksum()
{
	//Loop through each frequency change.
	ifstream boxFile("Boxes.txt");
	string line;

	//Stores the amount of lines with two and three same characters.
	int twoSameCharacters = 0;
	int threeSameCharacters = 0;

	while (getline(boxFile, line))
	{
		boxIDs.push_back(line);

		map<char, int> characterCount;

		//Loop through each character on the line and add their counts to the map.
		for (int i = 0; i < line.size(); i++)
		{
			characterCount[line[i]]++;
		}

		//Loop through all the counted characters and add to the two same and three same character counts
		//if they have two of the same or three of the same characters.
		map<char, int>::iterator it;
		bool hasTwoSame = false;
		bool hasThreeSame = false;

		for (it = characterCount.begin(); it != characterCount.end(); it++)
		{
			//The line has two characters the same.
			if (it->second == 2 && hasTwoSame == false)
			{
				twoSameCharacters++;
				hasTwoSame = true;
			}

			//The line has three characters the same.
			if (it->second == 3 && hasThreeSame == false)
			{
				threeSameCharacters++;
				hasThreeSame = true;
			}

			//Break as there is no point in continuing if both two same characters and three same characters have been found.
			if (hasTwoSame && hasThreeSame)
			{
				break;
			}
		}
	}

	boxFile.close();

	return twoSameCharacters * threeSameCharacters;
}

//Gets the common letters between the two correct box ID's.
string GetCommonLetters()
{
	//Loop through and compare all the Box ID's.
	for (int i = 0; i < boxIDs.size() - 1; i++)
	{
		for (int j = 1; j < boxIDs.size(); j++)
		{
			string sameCharacters;

			for (int k = 0; k < boxIDs[i].size(); k++)
			{
				//Count the number of same characters by adding them to the vector.
				if (boxIDs[i][k] == boxIDs[j][k])
				{
					sameCharacters.push_back(boxIDs[i][k]);
				}
			}

			//If only one character is different, break and return the same characters.
			if (sameCharacters.size() == boxIDs[i].size() - 1)
			{
				return sameCharacters;
			}
		}
	}
}