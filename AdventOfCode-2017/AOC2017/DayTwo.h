#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//Determines the difference between the largest and smallest values in a row and adds them together to get the checksum.
int GetChecksum()
{
	int checksum = 0;

	ifstream spreadsheetFile("Spreadsheet.txt");
	string line;

	//Loop through each row of the spreadsheet.
	while (getline(spreadsheetFile, line))
	{
		int lowest = INT_MAX;
		int highest = 0;

		string currentNumber = "";

		//Loop through each of the numbers.
		for (int i = 0; i < line.size(); i++)
		{
			//Read the next number.
			if (isdigit(line[i]))
			{
				currentNumber += line[i];
			}

			//Determine whether the number is lower than the lowest or
			//higher than the highest so far.
			else if (currentNumber != "")
			{
				int convertedNumber = stoi(currentNumber);

				//The current number is the lowest.
				if (convertedNumber < lowest)
				{
					lowest = convertedNumber;
				}

				//The current number is the highest.
				if (convertedNumber > highest)
				{
					highest = convertedNumber;
				}

				currentNumber = "";
			}
		}

		//Get the difference between the lowest and highest number and add it to the checksum.
		checksum += (highest - lowest);
	}

	return checksum;
}

//Gets the evenly divisible values in each row and adds their division result together to get the answer.
int GetDivisibleValues()
{
	int total = 0;

	ifstream spreadsheetFile("Spreadsheet.txt");
	string line;

	//Loop through each row of the spreadsheet.
	while (getline(spreadsheetFile, line))
	{
		vector<int> rowNumbers; //Stores all the numbers on the row.
		string currentNumber = "";

		//Loop through each of the numbers.
		for (int i = 0; i < line.size(); i++)
		{
			//Read the next number.
			if (isdigit(line[i]))
			{
				currentNumber += line[i];

				if (i == line.size() - 1)
				{
					rowNumbers.push_back(stoi(currentNumber));
					currentNumber = "";
				}
			}

			//Add the number to the rowNumbers list.
			else if (currentNumber != "")
			{
				rowNumbers.push_back(stoi(currentNumber));
				currentNumber = "";
			}
		}

		//Determine which numbers are evenly divisible and adds their division result to the total.
		for (int i = 0; i < rowNumbers.size() - 1; i++)
		{
			for (int j = i + 1; j < rowNumbers.size(); j++)
			{
				//If it is an even division, add the division result to the total.
				if (rowNumbers[i] % rowNumbers[j] == 0)
				{

					total += rowNumbers[i] / rowNumbers[j];
					break;
				}

				if (rowNumbers[j] % rowNumbers[i] == 0)
				{
					total += rowNumbers[j] / rowNumbers[i];
					break;
				}
			}
		}
	}

	return total;
}