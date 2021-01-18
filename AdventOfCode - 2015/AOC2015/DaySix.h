#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int lights[1000][1000];

//Executes all the lighting instructions and returns how many lights are lit.
int GetLitLights(int method)
{
	ifstream instructionsFile("Instructions.txt");
	string line;

	//Reset all the lights.
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			lights[i][j] = 0;
		}
	}

	//Loop through each instruction.
	while (getline(instructionsFile, line))
	{
		string currentSubString = "";
		int lightMode = 0; //0 = turn on which is default, 1 = turn off, 2 = toggle.

		int currentProgress = 0;
		int xLowerBound = 0;
		int xHigherBound = 0;
		int yLowerBound = 0;
		int yHigherBound = 0;

		for (int i = 0; i < line.size(); i++)
		{
			//Skip spaces and commas.
			if (line[i] != ' ' && line[i] != ',')
			{
				currentSubString += line[i];
			}

			else if (currentSubString != "turn")
			{
				currentSubString = "";
			}

			//Set the light mode.
			if (currentSubString == "turnoff")
			{
				lightMode = 1;
			}

			if (currentSubString == "toggle")
			{
				lightMode = 2;
			}

			//Set the x and y bounds based on currentProgress.
			if (i == line.size() - 1 || line[i + 1] == ',' || line[i + 1] == ' ')
			{
				if (isdigit(line[i]))
				{
					switch (currentProgress)
					{
					case 0:
						xLowerBound = stoi(currentSubString);
						break;

					case 1:
						yLowerBound = stoi(currentSubString);
						break;

					case 2:
						xHigherBound = stoi(currentSubString);
						break;

					case 3:
						yHigherBound = stoi(currentSubString);
						break;
					}

					currentSubString = "";
					currentProgress++;
				}
			}
		}

		//Loop through the lights in the defined lower and higher bounds.
		for (int i = xLowerBound; i <= xHigherBound; i++)
		{
			for (int j = yLowerBound; j <= yHigherBound; j++)
			{
				//Turn on
				if (lightMode == 0)
				{
					//Turn all the lights in the bounds on.
					if (method == 1)
					{
						lights[i][j] = 1;
					}

					//Increase the brightness of the lights in the bounds by 1.
					else
					{
						lights[i][j]++;
					}
				}

				//Turn off
				if (lightMode == 1)
				{
					//Turn all the lights in the bounds off.
					if (method == 1)
					{
						lights[i][j] = 0;
					}

					//Decrease the brightness of the lights in the bounds by 1 to a minimum of 0.
					else if (lights[i][j] > 0)
					{
						lights[i][j]--;
					}
				}

				//Toggle
				if (lightMode == 2)
				{
					//Toggle all the lights in the bounds.
					if (method == 1)
					{
						if (lights[i][j] == 1)
						{
							lights[i][j] = 0;
						}

						else
						{
							lights[i][j] = 1;
						}
					}

					//Increase the brightness of the lights in the bounds by 2.
					else
					{
						lights[i][j] += 2;
					}
				}
			}
		}
	}

	int litLights = 0;

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			//Count the amount of lit lights.
			if (method == 1)
			{
				if (lights[i][j] == 1)
				{
					litLights++;
				}
			}

			//Count the total amount of brightness from all the lights.
			else
			{
				litLights += lights[i][j];
			}
		}
	}

	instructionsFile.close();
	return litLights;
}