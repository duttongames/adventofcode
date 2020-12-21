#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

bool cubes[30][30][30];

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
				if (cubes[k][j][i] == true)
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

		cout << "Z: " + to_string(offset) << endl;
		offset++;
	}
}

//Checks if a cube is active. Returns 0 if not, 1 if yes.
int CheckActive(int cubeX, int cubeY, int cubeZ)
{
	if (cubeX > 0 && cubeY > 0 && cubeZ > 0 && cubeX < 30 && cubeY < 30 && cubeZ < 30)
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

	else
	{
		return 0;
	}
}

//Checks a single cube and returns the amount of active cubes adjacent to it.
int CheckCube(int cubeX, int cubeY, int cubeZ)
{
	int activeAdjacentCubes = 0;

	activeAdjacentCubes += CheckActive(cubeX, cubeY, cubeZ - 1);
	activeAdjacentCubes += CheckActive(cubeX, cubeY, cubeZ + 1);

	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY - 1, cubeZ - 1);
	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY, cubeZ - 1);
	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY + 1, cubeZ - 1);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY - 1, cubeZ - 1);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY, cubeZ - 1);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY + 1, cubeZ - 1);
	activeAdjacentCubes += CheckActive(cubeX, cubeY + 1, cubeZ - 1);
	activeAdjacentCubes += CheckActive(cubeX, cubeY - 1, cubeZ - 1);

	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY - 1, cubeZ);
	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY, cubeZ);
	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY + 1, cubeZ);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY - 1, cubeZ);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY, cubeZ);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY + 1, cubeZ);
	activeAdjacentCubes += CheckActive(cubeX, cubeY + 1, cubeZ);
	activeAdjacentCubes += CheckActive(cubeX, cubeY - 1, cubeZ);

	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY - 1, cubeZ + 1);
	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY, cubeZ + 1);
	activeAdjacentCubes += CheckActive(cubeX - 1, cubeY + 1, cubeZ + 1);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY - 1, cubeZ + 1);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY, cubeZ + 1);
	activeAdjacentCubes += CheckActive(cubeX + 1, cubeY + 1, cubeZ + 1);
	activeAdjacentCubes += CheckActive(cubeX, cubeY + 1, cubeZ + 1);
	activeAdjacentCubes += CheckActive(cubeX, cubeY - 1, cubeZ + 1);

	return activeAdjacentCubes;
}

//Performs a cycle and returns the number of active cubes left.
int Cycle()
{
	GetInitialState();

	int activeCubes = 0;
	int cubesCopy[30][30][30];

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				cubesCopy[i][j][k] = cubes[i][j][k];
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
					int adjacentCubes = CheckCube(i, j, k);

					if (cubes[i][j][k] == true)
					{
						if (adjacentCubes < 2 || adjacentCubes > 3)
						{
							cubesCopy[i][j][k] = false;
						}
					}

					else
					{
						if (adjacentCubes == 3)
						{
							cubesCopy[i][j][k] = true;
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
					cubes[i][j][k] = cubesCopy[i][j][k];
				}
			}
		}

		//GetCurrentState();
	}

	//Count the amount of active cubes.
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				if (cubes[i][j][k] == true)
				{
					activeCubes++;
				}
			}
		}
	}

	return activeCubes;
}