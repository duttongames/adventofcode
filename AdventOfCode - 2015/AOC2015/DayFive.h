#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Gets the amount of strings that are nice.
int GetNiceStrings(int method)
{
	ifstream stringFile("Strings.txt");
	string line;

	//The amount of strings that are nice.
	int niceStrings = 0;

	//Loop through each string.
	while (getline(stringFile, line))
	{
		//Part 1 Variables
		int vowelCount = 0;
		bool doubleLetter = false;
		bool containsBadString = false;

		//Part 2 Variables
		map<string, int> pairs;
		bool twoPairs = false;
		bool repeat = false;

		for (int i = 0; i < line.size(); i++)
		{
			//Use the first method for Part 1.
			if (method == 1)
			{
				//Increment the vowel counter when encountering a vowel.
				if (line[i] == 'a' || line[i] == 'e' || line[i] == 'i' || line[i] == 'o' || line[i] == 'u')
				{
					vowelCount++;
				}

				if (i < line.size() - 1)
				{
					//Set doubleLetter to true if there are two of the same characters in a row.
					if (line[i] == line[i + 1])
					{
						doubleLetter = true;
					}

					//Set containsBadString to true if it contains a substring that is not allowed.
					string currentSubString = std::string() + line[i] + line[i + 1];

					if (currentSubString == "ab" || currentSubString == "cd" || currentSubString == "pq" || currentSubString == "xy")
					{
						containsBadString = true;
					}
				}
			}

			//Use the second method for Part 2.
			else
			{
				if (i < line.size() - 1)
				{
					bool overlap = false;

					//Save each pair of letters if they don't overlap.
					if (i > 0)
					{
						string substringOne = std::string() + line[i - 1] + line[i];
						string substringTwo = std::string() + line[i] + line[i + 1];

						if (i > 1)
						{ 
							string substringThree = std::string() + line[i - 1] + line[i - 2];

							if (substringOne == substringTwo && substringThree != substringOne)
							{
								overlap = true;
							}
						}

						else
						{
							if (substringOne == substringTwo)
							{
								overlap = true;
							}
						}
					}

					if (overlap == false)
					{
						string currentSubString = std::string() + line[i] + line[i + 1];
						pairs[currentSubString]++;

						if (pairs[currentSubString] > 1)
						{
							twoPairs = true;
						}
					}
				}

				if (i < line.size() - 2)
				{
					//Set repeat to true if there are two of the same characters in a row with a letter between them.
					if (line[i] == line[i + 2])
					{
						repeat = true;
					}
				}
			}
		}

		//Increment the nice strings count if there are more than three vowels, at least one double letter and no bad substrings.
		if (method == 1)
		{
			if (vowelCount >= 3 && doubleLetter && containsBadString == false)
			{
				niceStrings++;
			}
		}

		//Increment the nice strings count if there are two pairs of the same string and a letter which repeats with a letter between them.
		else
		{
			if (twoPairs && repeat)
			{
				niceStrings++;
			}
		}
	}

	stringFile.close();
	return niceStrings;
}