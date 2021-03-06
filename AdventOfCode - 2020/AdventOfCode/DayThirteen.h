#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int earliestTimestamp = 0;
vector<int> availableBuses;

void ReadBusNotes(int method)
{
	string line;

	ifstream busNotes("BusNotes.txt");

	earliestTimestamp = 0;
	availableBuses.clear();

	int lineCounter = 0;

	if (method == 0)
	{
		//Get the input from the txt file.
		while (getline(busNotes, line))
		{
			//Get the earliest timestamp I can depart.
			if (lineCounter == 0)
			{
				earliestTimestamp = stoi(line);
			}

			//Get the ID's of the buses that are in service.
			else
			{
				string busID = "";

				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == ',' || line[i] == 'x' || i == line.size() - 1)
					{
						if (i == line.size() - 1)
						{
							busID += line[i];
						}

						if (busID.size() > 0)
						{
							availableBuses.push_back(stoi(busID));
							busID = "";
						}
					}

					else
					{
						busID += line[i];
					}
				}
			}

			lineCounter++;
		}
	}

	else
	{
	//Get the input from the txt file.
	while (getline(busNotes, line))
	{
		//Get the earliest timestamp I can depart.
		if (lineCounter == 0)
		{
			earliestTimestamp = stoi(line);
		}

		//Get the ID's of all buses.
		else
		{
			string busID = "";

			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == ',' || i == line.size() - 1)
				{
					if (i == line.size() - 1)
					{
						busID += line[i];
					}

					if (busID.size() > 0)
					{
						//Push x's as 1 since they have no time constraints.
						if (busID == "x")
						{
							busID = "1";
						}

						availableBuses.push_back(stoi(busID));
						busID = "";
					}
				}

				else
				{
					busID += line[i];
				}
			}
		}

		lineCounter++;
	}
	}
}

//Determines the earliest bus that can be taken and returns its ID multiplied by the minutes needed to wait.
int GetEarliestBus()
{
	int currentEarliestTime = 0;
	int earliestTime = INT_MAX;
	int earliestBusID = 0;

	for (int i = 0; i < availableBuses.size(); i++)
	{
		currentEarliestTime = availableBuses[i];

		while (currentEarliestTime < earliestTimestamp)
		{
			currentEarliestTime += availableBuses[i];
		}

		if (currentEarliestTime < earliestTime)
		{
			earliestTime = currentEarliestTime;
			earliestBusID = availableBuses[i];
		}
	}

	return earliestBusID * (earliestTime - earliestTimestamp);
}

long long gcd(long long int a, long long int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

long long lcm(int a, int b)
{
	return (a / gcd(a, b)) * b;
}

//Gets the earliest timestamp that all buses depart subsequently one after the other.
long long GetEarliestDeparture()
{
	long long earliestDeparture = 0;
	long long currentTimestamp = 0;
	long long incrementAmount = 1;

	//CREDIT GOES TO JOSHBDUNCAN FOR THIS SOLUTION https://gist.github.com/joshbduncan/65f810fe821c7a3ea81a1f5a444ea81e

	//Loop through each of the buses in the list.
	for (int i = 0; i < availableBuses.size(); i++)
	{
		//Increase the timestamp by the increment amount while the bus does not evenly divide by the current timestamp plus the offset.
		while ((currentTimestamp + i) % availableBuses[i] != 0)
		{
			currentTimestamp += incrementAmount;
		}

		//Increase the increment amount.
		incrementAmount *= availableBuses[i];
	}

	earliestDeparture = currentTimestamp;
	return earliestDeparture;
}