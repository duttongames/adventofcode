#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Counts the total sum of all the numbers in the document.
long CountNumbers()
{
	ifstream jsonFile("JSON.txt");
	string line;

	long total = 0;

	//Loop through line of the JSON.
	while (getline(jsonFile, line))
	{
		string currentNumber = "";

		for (int i = 0; i < line.size(); i++)
		{
			//If the line character is a digit, add it to the currentNumber string.
			if (isdigit(line[i]) || line[i] == '-')
			{
				currentNumber += line[i];
			}

			//If the current number isn't empty and the line character isn't a digit, add the number to the total.
			else if (currentNumber != "")
			{
				total += stoi(currentNumber);
				currentNumber = "";
			}
		}
	}

	jsonFile.close();

	return total;
}