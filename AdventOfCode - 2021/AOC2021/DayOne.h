#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Gets the number of times a measurement is larger than the previous.
int GetLargerMeasurements()
{
	ifstream depthFile("Depth.txt");
	string line;

	getline(depthFile, line);
	int current = stoi(line);

	int largerCount = 0;

	//Loop through each measurement.
	while (getline(depthFile, line))
	{
		if (stoi(line) > current)
		{
			largerCount++;
		}

		current = stoi(line);
	}

	depthFile.close();
	return largerCount;
}

//Gets the number of times a sum of three measurements is larger than the previous three.
int GetLargerMeasurementsSum()
{
	ifstream depthFile("Depth.txt");
	string line;

	getline(depthFile, line);
	int current = stoi(line);
	getline(depthFile, line);
	int currentTwo = stoi(line);
	getline(depthFile, line);
	int currentThree = stoi(line);

	int largerCount = 0;

	//Loop through each measurement.
	while (getline(depthFile, line))
	{
		if (stoi(line) + currentTwo + currentThree > current + currentTwo + currentThree)
		{
			largerCount++;
		}

		current = currentTwo;
		currentTwo = currentThree;
		currentThree = stoi(line);
	}

	depthFile.close();
	return largerCount;
}