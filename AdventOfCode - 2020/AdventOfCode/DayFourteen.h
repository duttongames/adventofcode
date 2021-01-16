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
map<string, string> memoryAddressesTwo;
bool flip = false;
int test = 0;

using namespace std;

void GetAllAddresses(vector<string> &addresses, string currentAddress)
{
	size_t currentPosition = currentAddress.find('X');

	if (currentAddress.find('X') == string::npos)
	{
		addresses.push_back(currentAddress);
	}

	else
	{
		currentAddress[currentPosition] = '0';
		GetAllAddresses(addresses, currentAddress);
		currentAddress[currentPosition] = '1';
		GetAllAddresses(addresses, currentAddress);
	}
}

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
	long long totalTwo = 0;
	vector<int> usedAddresses;
	vector<long long> valuesAdded;
	bool first = true;

	for (int i = 0; i < masks.size(); i++)
	{
		for (int j = 0; j < valuesToWrite[i].size(); j++)
		{
			string result = "000000000000000000000000000000000000";
			string oldResult = "000000000000000000000000000000000000";
			vector<string> results;

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

				oldResult[k] = valuesToWrite[i][j][k];
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

			//Version 2 Decoder Chip
			int xCount = 0;
			string startingAddress = bitset<36>(memoryAddresses[i][j]).to_string();

			for (int m = 0; m < masks[i].size(); m++)
			{
				if (masks[i][m] == 'X')
				{
					startingAddress[m] = 'X';
					xCount++;
				}

				if (masks[i][m] == '1')
				{
					startingAddress[m] = '1';
				}
			}

			GetAllAddresses(results, startingAddress);

			for (int m = 0; m < results.size(); m++)
			{
				if (memoryAddressesTwo.find(to_string(bitset<36>(results[m]).to_ullong())) != memoryAddressesTwo.end())
				{
					memoryAddressesTwo[to_string(bitset<36>(results[m]).to_ullong())] = oldResult;
				}

				else
				{
					memoryAddressesTwo.insert(pair<string, string>(to_string(bitset<36>(results[m]).to_ullong()), oldResult));
				}
			}

			test++;
		}
	}

	map<string, string>::iterator it;

	for (it = memoryAddressesTwo.begin(); it != memoryAddressesTwo.end(); it++)
	{
		totalTwo += bitset<36>(it->second).to_ullong();
	}

	cout << "The sum of all values in memory following the first method is: " + to_string(total) << endl;
	cout << "The sum of all values in memory following the second method is: " + to_string(totalTwo) << endl;
}