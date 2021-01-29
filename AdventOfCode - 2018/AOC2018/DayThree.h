#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int fabric[1000][1000];

//Determines how many square inches of fabric are in two or more claims or determines the claim that does not
//overlap with any other claims depending on the method.
int GetSquareInches(int method)
{
	ifstream fabricFile("Fabric.txt");
	string line;

	int counter = 0;
	int conflictingClaims = 0;

	//Loop through each fabric claim.
	while (getline(fabricFile, line))
	{
		int claimID = -1;
		int leftInches = -1;
		int topInches = -1;
		int width = -1;
		int height = -1;

		string currentValue = "";

		for (int i = 0; i < line.size(); i++)
		{
			//Add to the current value.
			if (isdigit(line[i]))
			{
				currentValue += line[i];

				//Get the height.
				if (i == line.size() - 1)
				{
					height = stoi(currentValue);
				}
			}

			else if (currentValue != "")
			{
				//Get the claim ID.
				if (claimID == -1)
				{
					claimID = stoi(currentValue);
				}

				//Get the left inches.
				else if (leftInches == -1)
				{
					leftInches = stoi(currentValue);
				}

				//Get the top inches.
				else if (topInches == -1)
				{
					topInches = stoi(currentValue);
				}

				//Get the width.
				else if (width == -1)
				{
					width = stoi(currentValue);
				}

				currentValue = "";
			}
		}

		//Add the claim to the fabric array.
		for (int i = leftInches + 1; i < leftInches + 1 + width; i++)
		{
			for (int j = topInches + 1; j < topInches + 1 + height; j++)
			{
				fabric[i][j]++;
			}
		}
	}

	fabricFile.close();

	ifstream fabricFileTwo("Fabric.txt");

	//Loop again to determine the claim that does not overlap with any other claims.
	if (method == 2)
	{
		//Loop through each fabric claim.
		while (getline(fabricFileTwo, line))
		{
			int claimID = -1;
			int leftInches = -1;
			int topInches = -1;
			int width = -1;
			int height = -1;
			bool overlap = false;

			string currentValue = "";

			for (int i = 0; i < line.size(); i++)
			{
				//Add to the current value.
				if (isdigit(line[i]))
				{
					currentValue += line[i];

					//Get the height.
					if (i == line.size() - 1)
					{
						height = stoi(currentValue);
					}
				}

				else if (currentValue != "")
				{
					//Get the claim ID.
					if (claimID == -1)
					{
						claimID = stoi(currentValue);
					}

					//Get the left inches.
					else if (leftInches == -1)
					{
						leftInches = stoi(currentValue);
					}

					//Get the top inches.
					else if (topInches == -1)
					{
						topInches = stoi(currentValue);
					}

					//Get the width.
					else if (width == -1)
					{
						width = stoi(currentValue);
					}

					currentValue = "";
				}
			}

			//Add the claim to the fabric array.
			for (int i = leftInches + 1; i < leftInches + 1 + width; i++)
			{
				for (int j = topInches + 1; j < topInches + 1 + height; j++)
				{
					//If the inch of fabric has more than one claim then there is overlap.
					if (fabric[i][j] > 2)
					{
						overlap = true;
					}

					fabric[i][j]++;
				}
			}

			//If there is no overlap, then this is the correct claim.
			if (!overlap)
			{
				fabricFileTwo.close();
				return claimID;
			}
		}
	}

	//Determine which square inches have conflicting claims by their claim amount being higher than 1.
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			if (fabric[i][j] > 1)
			{
				conflictingClaims++;
			}
		}
	}

	return conflictingClaims;
}