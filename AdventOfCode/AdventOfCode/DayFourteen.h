#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

vector<string> masks;
vector<vector<string>> valuesToWrite;
vector<vector<int>> memoryAddresses;

using namespace std;

void ReadInitProgram()
{
	string line;

	ifstream program("InitProgram.txt");

	int maskCounter = -1;
	vector<string> currentValues;
	vector<int> currentMemoryAddresses;

	//Get the input from the txt file.
	while (getline(program, line))
	{
		if (line.substr(0, 4) == "mask")
		{
			masks.push_back(line.substr(7));

			if (maskCounter != -1)
			{
				valuesToWrite.push_back(currentValues);
				memoryAddresses.push_back(currentMemoryAddresses);
				currentValues.clear();
				currentMemoryAddresses.clear();
			}

			maskCounter++;
		}

		else
		{
			bool startReading = false;
			string value = "";

			for (int i = 1; i < line.size(); i++)
			{
				if (startReading)
				{
					value += line[i];
				}

				if (line[i] == '[')
				{
					startReading = true;
				}

				if (line[i] == ']')
				{
					currentMemoryAddresses.push_back(stoi(value));
					startReading = false;
					value = "";
				}

				if (line[i - 1] == '=' && line[i] == ' ')
				{
					startReading = true;
				}
			}

			currentValues.push_back(bitset<36>(stol(value)).to_string());
		}
	}

	valuesToWrite.push_back(currentValues);
	memoryAddresses.push_back(currentMemoryAddresses);

	long long total = 0;
	vector<int> usedAddresses;
	vector<long long> valuesAdded;

	for (int i = 0; i < masks.size(); i++)
	{
		for (int j = 0; j < valuesToWrite[i].size(); j++)
		{
			string result = "000000000000000000000000000000000000";

			for (int k = 0; k < masks[i].size(); k++)
			{
				if (masks[i][k] == 'X')
				{
					result[k] = valuesToWrite[i][j][k];
				}

				else
				{
					result[k] = masks[i][k];
				}
			}

			bool addNewAddress = true;

			for (int l = 0; l < usedAddresses.size(); l++)
			{
				if (usedAddresses[l] == memoryAddresses[i][j])
				{
					total -= valuesAdded[l];
					valuesAdded[l] = bitset<36>(result).to_ullong();
					addNewAddress = false;
					break;
				}
			}

			if (addNewAddress)
			{
				usedAddresses.push_back(memoryAddresses[i][j]);
				valuesAdded.push_back(bitset<36>(result).to_ullong());
			}

			total += bitset<36>(result).to_ullong();
		}
	}

	cout << total << endl;
}