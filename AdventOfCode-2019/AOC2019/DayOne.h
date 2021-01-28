#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Simple function that gets the fuel requirement from the current mass.
int GetFuel(int mass)
{
	return floor(mass / 3) - 2;
}

//Gets the fuel required for a module using its mass and adds all the results together.
long GetFuelRequirements(int method)
{
	long totalFuelRequirement = 0;

	ifstream moduleFile("ModuleMass.txt");
	string line;

	//Loop through each line of instructions.
	while (getline(moduleFile, line))
	{
		bool finishedAddingFuel = true;
		int currentMass = stoi(line);
		
		if (method == 2)
		{
			finishedAddingFuel = false;
		}
		
		//Iteratively add fuel until the mass is less than or equal 0.
		do
		{
			int fuelReq = GetFuel(currentMass);

			//If the fuel requirement is 0 or less, end the loop.
			if (fuelReq <= 0)
			{
				finishedAddingFuel = true;
			}

			//Add to the total fuel requirement.
			else
			{
				totalFuelRequirement += fuelReq;
				currentMass = fuelReq;
			}
		} 
		while (finishedAddingFuel == false);
	}

	return totalFuelRequirement;
}