#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> commands;
int direction = 90; //0 = North 90 = East 180 = South 270 = West
int northSouthPosition = 0;
int eastWestPosition = 0;
int waypointNorthSouthPosition = 1;
int waypointEastWestPosition = 10;

void ReadCommands()
{
	string line;

	ifstream ferryCommands("Commands.txt");

	commands.clear();

	//Get the input from the txt file.
	while (getline(ferryCommands, line))
	{
		commands.push_back(line);
	}
}

//Get the ship's Manhattan distance after processing all the ferry commands.
int GetManhattanDistance()
{
	direction = 90;
	northSouthPosition = 0;
	eastWestPosition = 0;
	waypointNorthSouthPosition = 1;
	waypointEastWestPosition = 10;

	for (int i = 0; i < commands.size(); i++)
	{
		int value = stoi(commands[i].substr(1));
		char currentDirection = commands[i][0];

		//Change the direction of the ship.
		if (currentDirection == 'F')
		{
			switch (direction)
			{
				case 0:
					currentDirection = 'N';
					break;

				case 90:
					currentDirection = 'E';
					break;

				case 180:
					currentDirection = 'S';
					break;

				case 270:
					currentDirection = 'W';
					break;
			}
		}

		//Determine which action to take.
		switch (currentDirection)
		{
			case 'N':
				northSouthPosition += value;
				break;

			case 'S':
				northSouthPosition -= value;
				break;

			case 'E':
				eastWestPosition += value;
				break;

			case 'W':
				eastWestPosition -= value;
				break;

			case 'L':
				direction -= value;

				if (direction < 0)
				{
					direction += 360;
				}

				break;

			case 'R':
				direction += value;

				if (direction >= 360)
				{
					direction -= 360;
				}

				break;
		}
	}

	return abs(eastWestPosition) + abs(northSouthPosition);
}

//Get the ship's Manhattan distance after processing all the ferry commands using the second waypoint method.
int GetManhattanDistanceTwo()
{
	direction = 90;
	northSouthPosition = 0;
	eastWestPosition = 0;
	waypointNorthSouthPosition = 1;
	waypointEastWestPosition = 10;

	for (int i = 0; i < commands.size(); i++)
	{
		int value = stoi(commands[i].substr(1));
		char currentDirection = commands[i][0];
		int oldNorthSouth = waypointNorthSouthPosition;

		//Determine which action to take.
		switch (currentDirection)
		{
			case 'N':
				waypointNorthSouthPosition += value;
				break;

			case 'S':
				waypointNorthSouthPosition -= value;
				break;

			case 'E':
				waypointEastWestPosition += value;
				break;

			case 'W':
				waypointEastWestPosition -= value;
				break;

			case 'L':
				
				if (value == 90)
				{
					waypointNorthSouthPosition = waypointEastWestPosition;
					waypointEastWestPosition = -oldNorthSouth;
				}

				if (value == 180)
				{
					waypointNorthSouthPosition = -waypointNorthSouthPosition;
					waypointEastWestPosition = -waypointEastWestPosition;
				}

				if (value == 270)
				{
					waypointNorthSouthPosition = -waypointEastWestPosition;
					waypointEastWestPosition = oldNorthSouth;
				}

				break;

			case 'R':
				
				if (value == 90)
				{
					waypointNorthSouthPosition = -waypointEastWestPosition;
					waypointEastWestPosition = oldNorthSouth;
				}

				if (value == 180)
				{
					waypointNorthSouthPosition = -waypointNorthSouthPosition;
					waypointEastWestPosition = -waypointEastWestPosition;
				}

				if (value == 270)
				{
					waypointNorthSouthPosition = waypointEastWestPosition;
					waypointEastWestPosition = -oldNorthSouth;
				}

				break;

			//Move the ship forward towards the waypoint.
			case 'F':
				northSouthPosition += waypointNorthSouthPosition * value;
				eastWestPosition += waypointEastWestPosition * value;
				break;
			}
	}

	return abs(eastWestPosition) + abs(northSouthPosition);
}
