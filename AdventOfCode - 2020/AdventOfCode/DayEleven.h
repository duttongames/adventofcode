#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> currentLayout;

void ReadSeats()
{
	string line;

	ifstream seats("Seats.txt");

	currentLayout.clear();

	//Get the input from the txt file.
	while (getline(seats, line))
	{
		currentLayout.push_back(line);
	}
}

//Gets how many seats end up occupied when seating stabilises with a different set of rules..
int GetOccupiedSeats()
{
	int seatsChanged = 1;

	//Keep changing the state until it cannot change anymore.
	while (seatsChanged > 0)
	{
		seatsChanged = 0;
		vector<string> layoutCopy = currentLayout;

		for (int i = 0; i < layoutCopy.size(); i++)
		{
			for (int j = 0; j < layoutCopy[i].size(); j++)
			{
				int adjacentSeats = 0;

				//Determine the amount of adjacent seats.
				if (j > 0)
				{
					//Check seat directly to the left.
					if (layoutCopy[i][j - 1] == '#')
					{
						adjacentSeats++;
					}

					if (i > 0)
					{
						//Check seat diagonally up and to the left.
						if (layoutCopy[i - 1][j - 1] == '#')
						{
							adjacentSeats++;
						}
					}

					if (i < currentLayout.size() - 1)
					{
						//Check seat diagonally down and to the left.
						if (layoutCopy[i + 1][j - 1] == '#')
						{
							adjacentSeats++;
						}
					}
				}

				if (j < currentLayout[i].size() - 1)
				{
					//Check seat directly to the right.
					if (layoutCopy[i][j + 1] == '#')
					{
						adjacentSeats++;
					}

					if (i > 0)
					{
						//Check seat diagonally up and to the right.
						if (layoutCopy[i - 1][j + 1] == '#')
						{
							adjacentSeats++;
						}
					}

					if (i < currentLayout.size() - 1)
					{
						//Check seat diagonally down and to the right.
						if (layoutCopy[i + 1][j + 1] == '#')
						{
							adjacentSeats++;
						}
					}
				}

				//Check seat directly up.
				if (i > 0)
				{
					if (layoutCopy[i - 1][j] == '#')
					{
						adjacentSeats++;
					}
				}

				//Check seat directly down.
				if (i < currentLayout.size() - 1)
				{
					if (layoutCopy[i + 1][j] == '#')
					{
						adjacentSeats++;
					}
				}

				//Make the seat occupied if there are no occupied adjacent seats.
				if (layoutCopy[i][j] == 'L')
				{
					if (adjacentSeats <= 0)
					{
						currentLayout[i][j] = '#';
						seatsChanged++;
					}
				}

				//Make the seat unoccupied if there are four or more occupied adjacent seats.
				if (layoutCopy[i][j] == '#')
				{
					if (adjacentSeats >= 4)
					{
						currentLayout[i][j] = 'L';
						seatsChanged++;
					}
				}
			}
		}
	}

	int seatsOccupied = 0;

	for (int i = 0; i < currentLayout.size(); i++)
	{
		for (int j = 0; j < currentLayout[i].size(); j++)
		{
			if (currentLayout[i][j] == '#')
			{
				seatsOccupied++;
			}
		}
	}

	return seatsOccupied;
}

//Gets how many seats end up occupied when seating stabilises.
int GetOccupiedSeatsTwo()
{
	int seatsChanged = 1;

	//Keep changing the state until it cannot change anymore.
	while (seatsChanged > 0)
	{
		seatsChanged = 0;
		vector<string> layoutCopy = currentLayout;

		for (int i = 0; i < layoutCopy.size(); i++)
		{
			for (int j = 0; j < layoutCopy[i].size(); j++)
			{
				int adjacentSeats = 0;

				//Determine the amount of adjacent seats.
				
				//Check the seat directly left.
				for (int k = j - 1; k >= 0; k--)
				{
					if (layoutCopy[i][k] == 'L')
					{
						break;
					}

					if (layoutCopy[i][k] == '#')
					{
						adjacentSeats++;
						break;
					}
				}

				//Check the seat directly right.
				for (int k = j + 1; k < currentLayout[i].size(); k++)
				{
					if (layoutCopy[i][k] == 'L')
					{
						break;
					}

					if (layoutCopy[i][k] == '#')
					{
						adjacentSeats++;
						break;
					}
				}

				//Check the seat directly down.
				for (int k = i + 1; k < currentLayout.size(); k++)
				{
					if (layoutCopy[k][j] == 'L')
					{
						break;
					}

					if (layoutCopy[k][j] == '#')
					{
						adjacentSeats++;
						break;
					}
				}

				//Check the seat directly up.
				for (int k = i - 1; k >= 0; k--)
				{
					if (layoutCopy[k][j] == 'L')
					{
						break;
					}

					if (layoutCopy[k][j] == '#')
					{
						adjacentSeats++;
						break;
					}
				}

				//Check the seat diagonally up and left.
				int column = j - 1;

				for (int k = i - 1; k >= 0; k--)
				{
					if (column >= 0)
					{
						if (layoutCopy[k][column] == 'L')
						{
							break;
						}

						if (layoutCopy[k][column] == '#')
						{
							adjacentSeats++;
							break;
						}
					}

					else
					{
						break;
					}

					column--;
				}

				//Check the seat diagonally up and right.
				column = j + 1;

				for (int k = i - 1; k >= 0; k--)
				{
					if (column < layoutCopy[k].size())
					{
						if (layoutCopy[k][column] == 'L')
						{
							break;
						}

						if (layoutCopy[k][column] == '#')
						{
							adjacentSeats++;
							break;
						}
					}

					else
					{
						break;
					}

					column++;
				}

				//Check the seat diagonally down and left.
				column = j - 1;

				for (int k = i + 1; k < currentLayout.size(); k++)
				{
					if (column >= 0)
					{
						if (layoutCopy[k][column] == 'L')
						{
							break;
						}

						if (layoutCopy[k][column] == '#')
						{
							adjacentSeats++;
							break;
						}
					}

					else
					{
						break;
					}

					column--;
				}

				//Check the seat diagonally down and right.
				column = j + 1;

				for (int k = i + 1; k < layoutCopy.size(); k++)
				{
					if (column < layoutCopy[k].size())
					{
						if (layoutCopy[k][column] == 'L')
						{
							break;
						}

						if (layoutCopy[k][column] == '#')
						{
							adjacentSeats++;
							break;
						}
					}

					else
					{
						break;
					}

					column++;
				}

				//Make the seat occupied if there are no occupied adjacent seats.
				if (layoutCopy[i][j] == 'L')
				{
					if (adjacentSeats <= 0)
					{
						currentLayout[i][j] = '#';
						seatsChanged++;
					}
				}

				//Make the seat unoccupied if there are five or more occupied adjacent seats.
				if (layoutCopy[i][j] == '#')
				{
					if (adjacentSeats >= 5)
					{
						currentLayout[i][j] = 'L';
						seatsChanged++;
					}
				}
			}
		}
	}

	int seatsOccupied = 0;

	for (int i = 0; i < currentLayout.size(); i++)
	{
		for (int j = 0; j < currentLayout[i].size(); j++)
		{
			if (currentLayout[i][j] == '#')
			{
				seatsOccupied++;
			}
		}
	}

	return seatsOccupied;
}