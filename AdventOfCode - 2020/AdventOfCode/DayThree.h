#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int CountTrees(int xMovement, int yMovement)
{
	string line;

	ifstream slopeLayout("Slope.txt");

	int lineCount = 0;
	int trees = 0;
	int xPos = 0;

	while (getline(slopeLayout, line))
	{
		if (lineCount > 0 && lineCount % yMovement == 0)
		{
			for (int i = 0; i < xMovement; i++)
			{
				if (xPos < line.size() - 1)
				{
					xPos++;
				}

				else
				{
					xPos = 0;
				}
			}

			if (line[xPos] == '#')
			{
				trees++;
			}
		}

		lineCount++;
	}

	return trees;
}