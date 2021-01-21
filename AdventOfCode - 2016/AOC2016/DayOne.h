#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int xDistance = 0;
int yDistance = 0;

map<vector<int>, int> locationsVisited;
bool foundLocationVisitedTwice = false;

//Checks all the locations in a specified path and prints the block distance of a location if this
//is the second time visiting it.
void CheckLocationsInPath(int startingLocation, int endingLocation, bool x)
{
	//Loop through each location in the path.
	for (int j = startingLocation; j < endingLocation; j++)
	{
		//Check if this is the second time visiting this location.
		vector<int> distanceVector;

		//If the instructions change the x position...
		if (x)
		{
			distanceVector = { j, yDistance };
		}

		//If the instructions change the y position...
		else
		{
			distanceVector = { xDistance, j };
		}

		//If the location has been visited at least once...
		if (locationsVisited[distanceVector] >= 1)
		{
			//Output the location that has been visited twice.
			if (x)
			{
				cout << "The first location visited twice is " + to_string(abs(j + yDistance)) + " blocks away." << endl;
				foundLocationVisitedTwice = true;
			}

			else
			{
				cout << "The first location visited twice is " + to_string(abs(xDistance + j)) + " blocks away." << endl;
				foundLocationVisitedTwice = true;
			}
		}

		//Add the location that was visited to the map.
		locationsVisited[distanceVector]++;
	}
}

//Gets the distance to Easter Bunny HQ in blocks.
int GetBlockDistance()
{
	ifstream directionsFile("Directions.txt");
	string line;
	getline(directionsFile, line);

	int currentDirection = 0; //0 = North, 1 = East 2 = South 3 = West
	string currentInstruction = "";

	//Loop through each direction.
	for (int i = 0; i < line.size(); i++)
	{
		//Move as specificed and clear the current instruction.
		if (line[i] == ',' || i == line.size() - 1)
		{
			if (i == line.size() - 1)
			{
				currentInstruction += line[i];
			}

			//Turn 90 Degrees Right.
			if (currentInstruction[0] == 'R')
			{
				if (currentDirection < 3)
				{
					currentDirection++;
				}

				else
				{
					currentDirection = 0;
				}
			}

			//Turn 90 Degrees Left.
			else
			{
				if (currentDirection > 0)
				{
					currentDirection--;
				}

				else
				{
					currentDirection = 3;
				}
			}

			int formerX = xDistance;
			int formerY = yDistance;

			//Move the amount of blocks specified.
			switch (currentDirection)
			{
				//Move North.
				case 0:
					yDistance += stoi(currentInstruction.substr(1, currentInstruction.size()));
					break;

				//Move East.
				case 1:
					xDistance += stoi(currentInstruction.substr(1, currentInstruction.size()));
					break;

				//Move South.
				case 2:
					yDistance -= stoi(currentInstruction.substr(1, currentInstruction.size()));
					break;

				//Move West.
				case 3:
					xDistance -= stoi(currentInstruction.substr(1, currentInstruction.size()));
					break;
			}

			//Loop through all the locations visited following the last instruction if a location has not been visited twice yet.
			if (foundLocationVisitedTwice == false)
			{
				//Check locations following a horizontal path.
				if (xDistance != formerX)
				{
					if (xDistance > formerX)
					{
						CheckLocationsInPath(formerX + 1, xDistance, true);
					}

					else
					{
						CheckLocationsInPath(xDistance, formerX - 1, true);
					}
				}

				//Check locations following a vertical path.
				if (yDistance != formerY)
				{
					if (yDistance > formerY)
					{
						CheckLocationsInPath(formerY + 1, yDistance, false);
					}

					else
					{
						CheckLocationsInPath(yDistance, formerY - 1, false);
					}
				}
			}

			currentInstruction = "";
		}

		//Read the next instruction.
		else if (line[i] != ' ')
		{
			currentInstruction += line[i];
		}
	}

	directionsFile.close();
	return abs(xDistance + yDistance);
}