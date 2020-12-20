#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

vector<int> minValues;
vector<int> maxValues;
vector<int> ticketValues;
vector<vector<int>> valuesByRow;

int valuesOnLine = 0;

void ReadTickets()
{
	string line;

	ifstream tickets("Tickets.txt");

	minValues.clear();
	maxValues.clear();
	ticketValues.clear();

	bool minValue = true;
	bool readLine = true;
	bool readValue = false;
	bool nearbyTickets = false;

	//Get the input from the txt file.
	while (getline(tickets, line))
	{
		if (line == "your ticket:")
		{
			readLine = false;
		}

		if (readLine)
		{
			string currentValue = "";
			valuesOnLine = 0;

			for (int i = 0; i < line.size(); i++)
			{
				if (isdigit(line[i]))
				{
					readValue = true;
				}

				if (readValue)
				{
					currentValue += line[i];

					if (line[i] == '-' || line[i] == ',' || line[i] == ' ' || i == line.size() - 1)
					{
						if (nearbyTickets)
						{
							ticketValues.push_back(stoi(currentValue));
							valuesOnLine++;
						}

						else
						{
							if (minValue)
							{
								minValues.push_back(stoi(currentValue));
								minValue = false;
							}

							else
							{
								maxValues.push_back(stoi(currentValue));
								minValue = true;
							}
						}

						currentValue = "";
						readValue = false;
					}
				}
			}
		}

		if (line == "nearby tickets:")
		{
			readLine = true;
			nearbyTickets = true;
		}
	}
}

//Gets the error rate 
int GetErrorRate()
{
	int errorRate = 0;

	ReadTickets();

	for (int i = 0; i < ticketValues.size(); i++)
	{
		for (int j = 0; j < minValues.size(); j++)
		{
			if (ticketValues[i] >= minValues[j] && ticketValues[i] <= maxValues[j])
			{
				break;
			}

			if (j == minValues.size() - 1)
			{
				errorRate += ticketValues[i];
				ticketValues.erase(ticketValues.begin() + i);
			}
		}
	}

	return errorRate;
}

//Works out which field is which and returns the Departure field values multiplied together.
int GetDepartureValues()
{
	int correctValues[3] = { 0 };

	int multiple = 0;

	for (int k = 0; k < ticketValues.size() / valuesOnLine; k++)
	{
		for (int i = k; i < ticketValues.size(); i += valuesOnLine)
		{
			for (int j = 0; j < minValues.size(); j += 2)
			{
				if (ticketValues[i] >= minValues[j] && ticketValues[i] <= maxValues[j])
				{
					correctValues[((j + 2) / 2) - 1]++;
				}

				else if (ticketValues[i] >= minValues[j + 1] && ticketValues[i] <= maxValues[j + 1])
				{
					correctValues[((j + 2) / 2) - 1]++;
				}
			}

			multiple++;
		}

		cout << "New Column: " << endl;

		for (int l = 0; l < valuesOnLine; l++)
		{
			cout << correctValues[l] << endl;
			correctValues[l] = 0;
		}
	}

	return 0;
}