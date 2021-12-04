#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Intcode.h"

using namespace std;

vector<int> integers;

//Reads an intcode program and stores it in a vector.
void ReadProgram()
{
	ifstream gravityFile("GravityProgram.txt");
	string line;
	getline(gravityFile, line);

	string currentInt = "";

	//Loop through the intcode program and add each integer to the integers vector.
	for (int i = 0; i < line.size(); i++)
	{
		//Ignore commas.
		if (line[i] != ',')
		{
			currentInt += line[i];
		}

		if (line[i] == ',' || i == line.size() - 1)
		{
			integers.push_back(stoi(currentInt));
			currentInt = "";
		}
	}
}

//Runs the gravity intcode program and returns either the value in 0 after running the program with a noun of 12 and verb of 2,
//or finds a noun and verb that produces 19690720 and returns 100 * noun + verb.
int RunGravityProgram(int method)
{
	//The noun and verb that produces 19690720 is between 0 and 99 so test each combination of those numbers.
	for (int currentNoun = 0; currentNoun < 100; currentNoun++)
	{
		for (int currentVerb = 0; currentVerb < 100; currentVerb++)
		{
			vector<int> integersCopy;
			int currentStep = 0;
			int opcode = 0;
			int valueOne = 0;
			int valueTwo = 0;

			//Make a copy of the integers vector so memory is reset on each loop.
			for (int i = 0; i < integers.size(); i++)
			{
				integersCopy.push_back(integers[i]);
			}

			//Use either the currentNoun and currentVerb or 12 and 2 depending on the method.
			if (method != 1)
			{
				integersCopy[1] = currentNoun;
				integersCopy[2] = currentVerb;
			}

			else
			{
				integersCopy[1] = 12;
				integersCopy[2] = 2;
			}

			//Loop through the intcode program.
			for (int i = 0; i < integersCopy.size(); i++)
			{
				//Determine which action to take.
				switch (currentStep)
				{
					//Get the opcdode.
					case 0:
						opcode = integersCopy[i];
						break;

					//Get the first value.
					case 1:
						valueOne = integersCopy[integersCopy[i]];
						break;

					//Get the second value.
					case 2:
						valueTwo = integersCopy[integersCopy[i]];
						break;

					//Perform the opcode oepration.
					case 3:
						integersCopy[integersCopy[i]] = IntcodeOps(opcode, 0, valueOne, valueTwo);
						break;
				}

				//Break if encountering opcode 99(program exit).
				if (opcode == 99)
				{
					break;
				}

				currentStep++;

				//Reset the steps.
				if (currentStep == 4)
				{
					opcode = 0;
					valueOne = 0;
					valueTwo = 0;
					currentStep = 0;
				}
			}

			//Return the value in memory address 0 if using the first method.
			if (method == 1)
			{
				return integersCopy[0];
			}

			//Return 100 * noun + verb if the value in memory address 0 is 19690720.
			else if (integersCopy[0] == 19690720)
			{
				return 100 * currentNoun + currentVerb;
			}
		}
	}

	return 0;
}