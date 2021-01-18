#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

map<string, unsigned int> circuits;

//Outputs the value of every circuit. Used for debugging.
void OutputCircuits()
{
	map<string, unsigned int>::iterator it;

	for (it = circuits.begin(); it != circuits.end(); it++)
	{
		cout << it->first + ": " + to_string(it->second) << endl;
	}
}

//Assembles the circuity following the instructions and returns the value left in 'a'.
int AssembleCircuit()
{
	ifstream circuitFile("Circuit.txt");
	string line;

	//Loop through each circuit instruction.
	while (getline(circuitFile, line))
	{
		string firstValue = "";
		string secondValue = "";
		string currentValue = "";
		string currentOperation = "";
		string targetValue = "";
		bool skipSecondValue = false;
		
		//Read and parse the command from the file.
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != ' ' && line[i] != '-' && line[i] != '>')
			{
				currentValue += line[i];
			}

			if (i == line.size() - 1 || line[i] == ' ' || line[i] == '-' || line[i] == '>')
			{
				//Skip the second value and operator.
				if (line[i] == '-')
				{
					skipSecondValue = true;
				}

				//Get the first value to parse.
				if (firstValue == "")
				{
					if (currentValue == "NOT")
					{
						currentOperation = currentValue;
					}

					else
					{
						firstValue = currentValue;
					}
				}

				//Get the operator to parse.
				else if (currentOperation == "" && skipSecondValue == false)
				{
					currentOperation = currentValue;
				}

				//Get the second value to parse.
				else if (secondValue == "" && skipSecondValue == false)
				{
					secondValue = currentValue;
				}

				//Get the circuit to set the value of.
				else if (targetValue == "")
				{
					targetValue = currentValue;
				}

				currentValue = "";
			}
		}

		//Set the target circuit's value to the first value if there is no operator.
		if (currentOperation == "")
		{
			//Set the target circuit's value to a number.
			if (isdigit(firstValue[0]))
			{
				circuits[targetValue] = stoul(firstValue);
			}

			//Set the target circuit's value to another circuit's value.
			else
			{
				circuits[targetValue] = circuits[firstValue];
			}
		}

		//Perform a Bitwise AND Operation on the two values and set the target circuit's value to it.
		if (currentOperation == "AND")
		{
			if (isdigit(firstValue[0]))
			{
				circuits[targetValue] = stoi(firstValue) & circuits[secondValue];
			}

			else
			{
				circuits[targetValue] = circuits[firstValue] & circuits[secondValue];
			}
		}

		//Perform a Bitwise OR Operation on the two values and set the target circuit's value to it.
		if (currentOperation == "OR")
		{
			circuits[targetValue] = circuits[firstValue] | circuits[secondValue];
		}

		//Perform a Bitwise Left Shift Operation on the two values and set the target circuit's value to it.
		if (currentOperation == "LSHIFT")
		{
			circuits[targetValue] = circuits[firstValue] << stoi(secondValue);
		}

		//Perform a Bitwise Right Shift Operation on the two values and set the target circuit's value to it.
		if (currentOperation == "RSHIFT")
		{
			circuits[targetValue] = circuits[firstValue] >> stoi(secondValue);
		}

		//Perform a Bitwise NOT Operation on the first value and set the target circuit's value to it.
		if (currentOperation == "NOT")
		{
			circuits[targetValue] = bitset<16>(~circuits[firstValue]).to_ulong();
		}
	}

	//OutputCircuits();

	return circuits["a"];
}