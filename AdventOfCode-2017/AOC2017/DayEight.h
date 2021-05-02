#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

map<string, int> registers;

//Computes a set of register instructions.
void ComputeInstructions()
{
	ifstream registerFile("Register.txt");
	string line;

	int highestValue = 0;

	//Loop through each register instruction and carry it out.
	while (getline(registerFile, line))
	{
		string registerOne = "";
		string command = "";
		int numberOne = INT_MAX;
		string registerTwo = "";
		string comparison = "";
		int numberTwo = INT_MAX;

		string currentPart = "";

		//Loop through each part of the instruction and determine what to do.
		for (int i = 0; i < line.size(); ++i)
		{
			//Add non-space characters to the current part.
			if (line[i] != ' ')
			{
				currentPart += line[i];
			}

			//Store the current part in the correct variable.
			if (line[i] == ' ' || i == line.size() - 1)
			{
				if (registerOne == "")
				{
					registerOne = currentPart;
				}

				else if (command == "")
				{
					command = currentPart;
				}

				else if (numberOne == INT_MAX)
				{
					numberOne = stoi(currentPart);
				}

				else if (currentPart != "if")
				{
					if (registerTwo == "")
					{
						registerTwo = currentPart;
					}

					else if (comparison == "")
					{
						comparison = currentPart;
					}

					else
					{
						numberTwo = stoi(currentPart);
					}
				}

				currentPart = "";
			}
		}

		//Determine whether to execute the instruction.
		bool executeInstruction = false;

		//Greater than
		if (comparison == ">")
		{
			if (registers[registerTwo] > numberTwo)
			{
				executeInstruction = true;
			}
		}

		//Greater than or equal to
		if (comparison == ">=")
		{
			if (registers[registerTwo] >= numberTwo)
			{
				executeInstruction = true;
			}
		}

		//Less than
		if (comparison == "<")
		{
			if (registers[registerTwo] < numberTwo)
			{
				executeInstruction = true;
			}
		}

		//Less than or equal to
		if (comparison == "<=")
		{
			if (registers[registerTwo] <= numberTwo)
			{
				executeInstruction = true;
			}
		}

		//Equal to
		if (comparison == "==")
		{
			if (registers[registerTwo] == numberTwo)
			{
				executeInstruction = true;
			}
		}

		//Not equal to
		if (comparison == "!=")
		{
			if (registers[registerTwo] != numberTwo)
			{
				executeInstruction = true;
			}
		}

		//Execute the instruction if the condition was met.
		if (executeInstruction)
		{
			//Increase the value in the register.
			if (command == "inc")
			{
				registers[registerOne] += numberOne;
			}

			//Decrease the value in the register.
			if (command == "dec")
			{
				registers[registerOne] -= numberOne;
			}

			//Check if the new value is the highest yet.
			if (registers[registerOne] > highestValue)
			{
				highestValue = registers[registerOne];
			}
		}
	}

	//Output the highest value held in a register during the process.
	cout << "The highest value held while executing the instructions is: " + to_string(highestValue) << endl;
}

//Finds the highest value in the registers and returns it.
int FindHighestValue()
{
	map<string, int>::iterator regIterator;

	int highestValue = INT_MIN;

	//Loop through all of the register values.
	for (regIterator = registers.begin(); regIterator != registers.end(); regIterator++)
	{
		if (regIterator->second > highestValue)
		{
			highestValue = regIterator->second;
		}
	}

	return highestValue;
}