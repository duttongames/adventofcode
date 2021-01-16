#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

vector<int> minValues;
vector<int> maxValues;
vector<vector<int>> ticketValues;
vector<vector<int>> errorFreeValues;
vector<int> yourTicket;

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
	bool readMyTicket = false;
	bool readValue = false;
	bool nearbyTickets = false;
	int lineCounter = 0;

	//Get the input from the txt file.
	while (getline(tickets, line))
	{
		vector<int> emptyTicket;

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
				if (readMyTicket)
				{
					if (line[i] == ',')
					{
						yourTicket.push_back(stoi(currentValue));
						currentValue = "";
					}

					else
					{
						currentValue += line[i];
					}

					if (i == line.size() - 1)
					{
						yourTicket.push_back(stoi(currentValue));
						currentValue = "";
						readMyTicket = false;
					}
				}

				else if (isdigit(line[i]))
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
							emptyTicket.push_back(stoi(currentValue));
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

		if (line == "your ticket:")
		{
			readMyTicket = true;
			readLine = true;
		}

		if (line == "nearby tickets:")
		{
			readLine = true;
			nearbyTickets = true;
		}

		if (emptyTicket.size() > 0)
		{
			ticketValues.push_back(emptyTicket);
		}

		lineCounter++;
	}
}

//Gets the error rate 
int GetErrorRate()
{
	int errorRate = 0;
	int columnCounter = 0;
	vector<int> invalidTickets;

	ReadTickets();

	while (columnCounter < ticketValues[0].size())
	{
		for (int i = 0; i < ticketValues.size(); i++)
		{
			for (int j = 0; j < minValues.size(); j += 2)
			{
				if (ticketValues[i][columnCounter] >= minValues[j] && ticketValues[i][columnCounter] <= maxValues[j])
				{
					break;
				}

				if (ticketValues[i][columnCounter] >= minValues[j + 1] && ticketValues[i][columnCounter] <= maxValues[j + 1])
				{
					break;
				}

				if (j >= minValues.size() - 2)
				{
					errorRate += ticketValues[i][columnCounter];
					invalidTickets.push_back(i);
				}
			}

			if (columnCounter == ticketValues[0].size() - 1 && find(invalidTickets.begin(), invalidTickets.end(), i) == invalidTickets.end())
			{
				errorFreeValues.push_back(ticketValues[i]);
			}
		}

		columnCounter++;
	}

	return errorRate;
}

//Works out which field is which and returns the Departure field values multiplied together.
long long GetDepartureValues()
{
	int columnCounter = 0;
	int minCounter = 0;
	map<int, vector<int>> possibleTicketFields;

	while (columnCounter < errorFreeValues[0].size())
	{
		vector<int> validTickets;

		for (int i = 0; i < minValues.size() / 2; i++)
		{
			validTickets.push_back(0);
		}

		for (int i = 0; i < errorFreeValues.size(); i++)
		{
			for (int j = 0; j < minValues.size(); j += 2)
			{
				if (errorFreeValues[i][columnCounter] >= minValues[j] && errorFreeValues[i][columnCounter] <= maxValues[j])
				{
					if (j == 0)
					{
						validTickets[j]++;
					}

					else
					{
						validTickets[j / 2]++;
					}
				}

				else if (errorFreeValues[i][columnCounter] >= minValues[j + 1] && errorFreeValues[i][columnCounter] <= maxValues[j + 1])
				{
					if (j == 0)
					{
						validTickets[j]++;
					}

					else
					{
						validTickets[j / 2]++;
					}
				}
			}
		}

		for (int i = 0; i < validTickets.size(); i++)
		{
			possibleTicketFields[i].push_back(validTickets[i]);
		}

		columnCounter++;
	}

	int currentCount = 1;
	map<int, int> foundFields;

	for (int i = 0; i < possibleTicketFields.size(); i++)
	{
		foundFields[i] = -1;
	}

	while (currentCount < possibleTicketFields.size() + 1)
	{
		for (int i = 0; i < possibleTicketFields.size(); i++)
		{
			int possibleField = -1;
			int maxCount = 0;

			for (int j = 0; j < possibleTicketFields[i].size(); j++)
			{
				if (possibleTicketFields[i][j] == (possibleTicketFields.size() - 1) * 10)
				{
					if (possibleField == -1 && foundFields[j] == -1)
					{
						possibleField = j;
					}

					maxCount++;
				}
			}

			if (maxCount == currentCount)
			{
				foundFields[possibleField] = i;
				currentCount++;
			}
		}
	}

	long long departureValue = 1;

	for (int i = 0; i < foundFields.size(); i++)
	{
		if (foundFields[i] < 6)
		{
			departureValue *= yourTicket[i];
		}
	}

	return departureValue;
}