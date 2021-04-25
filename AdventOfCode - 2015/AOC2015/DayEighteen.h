#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

char lightGrid[100][100];
char gridCopy[100][100];

int method = 1;

//Checks if a specified light is on.
int CheckActive(int rowNumber, int columnNumber)
{
	if (gridCopy[rowNumber][columnNumber] == '#')
	{
		return 1;
	}

	return 0;
}

//Animates the light grid for a single step.
void NextStep()
{
	//Make a copy of the light grid.
	for (int i = 0; i < sizeof(lightGrid) / sizeof(lightGrid[0]); ++i)
	{
		for (int j = 0; j < sizeof(lightGrid[0]) / sizeof(lightGrid[0][0]); ++j)
		{
			gridCopy[i][j] = lightGrid[i][j];
		}
	}

	//Loop through all the lights.
	for (int i = 0; i < sizeof(lightGrid) / sizeof(lightGrid[0]); ++i)
	{
		for (int j = 0; j < sizeof(lightGrid[0]) / sizeof(lightGrid[0][0]); ++j)
		{
			//Count the number of adjacent neighbours to the current light that are turned on.
			int litNeighbours = 0;

			if (i > 0)
			{
				//Check the light directly up.
				litNeighbours += CheckActive(i - 1, j);

				//Check the light in the upper left.
				if (j > 0)
				{
					litNeighbours += CheckActive(i - 1, j - 1);
				}

				//Check the light in the upper right.
				if (j < sizeof(lightGrid) / sizeof(lightGrid[0]) - 1)
				{
					litNeighbours += CheckActive(i - 1, j + 1);
				}
			}

			if (i < sizeof(lightGrid) / sizeof(lightGrid[0]) - 1)
			{
				//Check the light directly down
				litNeighbours += CheckActive(i + 1, j);

				//Check the light in the bottom left.
				if (j > 0)
				{
					litNeighbours += CheckActive(i + 1, j - 1);
				}

				//Check the light in the bottom right.
				if (j < sizeof(lightGrid) / sizeof(lightGrid[0]) - 1)
				{
					litNeighbours += CheckActive(i + 1, j + 1);
				}
			}

			if (j > 0)
			{
				//Check the light directly to the left.
				litNeighbours += CheckActive(i, j - 1);
			}

			if (j < sizeof(lightGrid) / sizeof(lightGrid[0]) - 1)
			{
				//Check the light directly to the right.
				litNeighbours += CheckActive(i, j + 1);
			}

			//If the light is on and number of lit neighbours is not 2 or 3, turn the light off.
			if (gridCopy[i][j] == '#' && litNeighbours != 2 && litNeighbours != 3)
			{
				lightGrid[i][j] = '.';
			}

			//If the light is off and number of lit neighbours is 3, turn the light on.
			else if (gridCopy[i][j] == '.' && litNeighbours == 3)
			{
				lightGrid[i][j] = '#';
			}
		}
	}

	//If the method is 1, make sure the four corners are ALWAYS on for Part 2.
	if (method == 1)
	{
		int gridSize = sizeof(lightGrid) / sizeof(lightGrid[0]) - 1;

		lightGrid[0][0] = '#';
		lightGrid[gridSize][0] = '#';
		lightGrid[0][gridSize] = '#';
		lightGrid[gridSize][gridSize] = '#';
	}
}

//Returns the amount of lights that are turned on after the specified amount of steps from the initial configuration.
int GetLights(int steps)
{
	ifstream configFile("InitialConfig.txt");
	string line;

	int rowNumber = 0;

	//Get the initial configuration of the light grid and store it in a 2D Array.
	while (getline(configFile, line))
	{
		for (int columnNumber = 0; columnNumber < line.size(); ++columnNumber)
		{
			lightGrid[rowNumber][columnNumber] = line[columnNumber];
		}

		rowNumber++;
	}

	//If the method is 1, make sure the four corners are ALWAYS on for Part 2.
	if (method == 1)
	{
		int gridSize = sizeof(lightGrid) / sizeof(lightGrid[0]) - 1;

		lightGrid[0][0] = '#';
		lightGrid[gridSize][0] = '#';
		lightGrid[0][gridSize] = '#';
		lightGrid[gridSize][gridSize] = '#';
	}

	//Animate the light grid for the specified number of steps.
	for (int i = 0; i < steps; ++i)
	{
		NextStep();
	}

	//Count the amount of lights that are turned on and return the value.
	int lights = 0;

	for (int i = 0; i < sizeof(lightGrid) / sizeof(lightGrid[0]); ++i)
	{
		for (int j = 0; j < sizeof(lightGrid[0]) / sizeof(lightGrid[0][0]); ++j)
		{
			//The light is on, so add to the count.
			if (lightGrid[i][j] == '#')
			{
				lights++;
			}
		}
	}

	return lights;
}