#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Works out the depth and horizontal position after following the commands and returns the horizontal position times the depth.
int CalculatePosition()
{
	ifstream commandFile("Commands.txt");
	string line;

	int horizontalPosition = 0;
	int depth = 0;

	string command;

	//Loop through each measurement.
	while (getline(commandFile, line))
	{		
		command = "";

		for (int i = 0; i < line.size() - 2; ++i)
		{
			command += line[i];
		}

		if (command == "forward")
		{
			horizontalPosition += line[line.size() - 1] - '0';
		}

		if (command == "down")
		{
			depth += line[line.size() - 1] - '0';
		}

		if (command == "up")
		{
			depth -= line[line.size() - 1] - '0';
		}
	}

	return horizontalPosition * depth;
}

//Works out the depth and horizontal position after following the commands and returns the horizontal position times the depth.
//This function uses the new 'aim' parameter too.
int CalculatePositionAim()
{
	ifstream commandFile("Commands.txt");
	string line;

	int horizontalPosition = 0;
	int depth = 0;
	int aim = 0;

	string command;

	//Loop through each measurement.
	while (getline(commandFile, line))
	{
		command = "";

		for (int i = 0; i < line.size() - 2; ++i)
		{
			command += line[i];
		}

		if (command == "forward")
		{
			horizontalPosition += line[line.size() - 1] - '0';
			depth += aim * (line[line.size() - 1] - '0');
		}

		if (command == "down")
		{
			aim += line[line.size() - 1] - '0';
		}

		if (command == "up")
		{
			aim -= line[line.size() - 1] - '0';
		}
	}

	return horizontalPosition * depth;
}