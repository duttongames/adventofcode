#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

bool cubes[30][30][30];
auto fourDimCubes = new bool[30][30][30][30]();
bool looped = false;

//Reads and inputs the initial state of the cubes.
void GetInitialState()
{
	ifstream initialState("Cubes.txt");
	string line = "";

	int y = 14;

	//Get the input from the txt file.
	while (getline(initialState, line))
	{
		for (int x = 0; x < line.size(); x++)
		{
			if (line[x] == '#')
			{
				cubes[x + 14][y][18] = true;
				fourDimCubes[x + 14][y][14][14] = true;
			}
		}

		y++;
	}
}

//Outputs the current state of the cubes for debugging.
void GetCurrentState()
{
	int offset = -7;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				for (int l = 0; l < 30; l++)
				{
					if (fourDimCubes[k][j][i][l] == true)
					{
						cout << "#";
					}

					else
					{
						cout << ".";
					}
				}

				cout << endl;
			}

			cout << endl;
		}

		cout << "Z: " + to_string(offset) << endl;
		offset++;
	}
}

//Checks if a cube is active. Returns 0 if not, 1 if yes.
int CheckActive(int cubeX, int cubeY, int cubeZ, int cubeW)
{
	if (cubeX >= 0 && cubeY >= 0 && cubeZ >= 0 && cubeX < 30 && cubeY < 30 && cubeZ < 30)
	{
		if (cubeW == INT_MAX)
		{
			if (cubes[cubeX][cubeY][cubeZ] == true)
			{
				return 1;
			}

			else
			{
				return 0;
			}
		}

		else if (cubeW >= 0 && cubeW < 30)
		{
			if (fourDimCubes[cubeX][cubeY][cubeZ][cubeW] == true)
			{
				return 1;
			}

			else
			{
				return 0;
			}
		}
	}

	else
	{
		return 0;
	}
}

//Checks a single cube and returns the amount of active cubes adjacent to it.
int CheckCube(int cubeX, int cubeY, int cubeZ, int cubeW)
{
	int activeAdjacentCubes = 0;

	int loopCount = 0;

	if (cubeW != INT_MAX)
	{
		for (int i = cubeX - 1; i < cubeX + 2; i++)
		{
			for (int j = cubeY - 1; j < cubeY + 2; j++)
			{
				for (int k = cubeZ - 1; k < cubeZ + 2; k++)
				{
					for (int l = cubeW - 1; l < cubeW + 2; l++)
					{
						if (i == cubeX && j == cubeY && k == cubeZ && l == cubeW)
						{

						}

						else
						{
							activeAdjacentCubes += CheckActive(i, j, k, l);
							loopCount++;
						}
					}
				}
			}
		}
	}

	else
	{
		for (int i = cubeX - 1; i < cubeX + 2; i++)
		{
			for (int j = cubeY - 1; j < cubeY + 2; j++)
			{
				for (int k = cubeZ - 1; k < cubeZ + 2; k++)
				{
					if (i == cubeX && j == cubeY && k == cubeZ)
					{

					}

					else
					{
						activeAdjacentCubes += CheckActive(i, j, k, INT_MAX);
						loopCount++;
					}
				}
			}
		}
	}

	if (looped == false)
	{
		cout << to_string(loopCount) << endl;
		looped = true;
	}

	return activeAdjacentCubes;
}

//Performs a cycle and returns the number of active cubes left.
int Cycle()
{
	GetInitialState();

	int activeCubes = 0;
	auto fourDimCubesCopy = new bool[30][30][30][30]();

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				for (int w = 0; w < 30; w++)
				{
					fourDimCubesCopy[i][j][k][w] = fourDimCubes[i][j][k][w];
				}
			}
		}
	}

	//Cycle six times.
	for (int cycle = 0; cycle < 6; cycle++)
	{
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				for (int k = 0; k < 30; k++)
				{
					for (int w = 0; w < 30; w++)
					{
						int adjacentCubes = CheckCube(i, j, k, w);

						if (fourDimCubes[i][j][k][w] == true)
						{
							if (adjacentCubes < 2 || adjacentCubes > 3)
							{
								fourDimCubesCopy[i][j][k][w] = false;
							}
						}

						else
						{
							if (adjacentCubes == 3)
							{
								fourDimCubesCopy[i][j][k][w] = true;
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				for (int k = 0; k < 30; k++)
				{
					for (int w = 0; w < 30; w++)
					{
						fourDimCubes[i][j][k][w] = fourDimCubesCopy[i][j][k][w];
					}
				}
			}
		}
	}

	//Count the amount of active cubes.
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				for (int w = 0; w < 30; w++)
				{
					if (fourDimCubes[i][j][k][w] == true)
					{
						activeCubes++;
					}
				}
			}
		}
	}

	return activeCubes;
}