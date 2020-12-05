#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int GetHighestID()
{
	string line;

	ifstream seats("SeatIDs.txt");

	vector<int> rows;
	vector<int> columns;
	vector<int> seatIDs;

	int highestID = 0;

	for (int i = 0; i < 128; i++)
	{
		rows.push_back(i);
	}

	for (int i = 0; i < 8; i++)
	{
		columns.push_back(i);
	}

	while (getline(seats, line))
	{
		vector<int> currentRows = rows;
		vector<int> currentColumns = columns;

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == 'F')
			{
				currentRows.erase(currentRows.begin() + currentRows.size() / 2, currentRows.end());
			}

			else if (line[i] == 'B')
			{
				currentRows.erase(currentRows.begin(), currentRows.begin() + (currentRows.size() / 2));
			}

			else if (line[i] == 'L')
			{
				currentColumns.erase(currentColumns.begin() + currentColumns.size() / 2, currentColumns.end());
			}

			else if (line[i] == 'R')
			{
				currentColumns.erase(currentColumns.begin(), currentColumns.begin() + (currentColumns.size() / 2));
			}
		}
		
		int id = currentRows[0] * 8 + currentColumns[0];
		seatIDs.push_back(id);

		if (id > highestID)
		{
			highestID = id;
		}
	}

	cout << "Highest Seat ID: " + to_string(highestID) << endl;

	bool sorted = false;

	while (sorted == false)
	{
		sorted = true;

		for (int i = 0; i < seatIDs.size() - 1; i++)
		{
			if (seatIDs[i + 1] < seatIDs[i])
			{
				int temp = seatIDs[i];
				seatIDs[i] = seatIDs[i + 1];
				seatIDs[i + 1] = temp;

				sorted = false;
			}
		}
	}

	int missingID;

	for (int i = 0; i < seatIDs.size() - 1; i++)
	{
		if (seatIDs[i + 1] - seatIDs[i] > 1)
		{
			missingID = seatIDs[i + 1] - 1;
		}
	}

	return missingID;
}