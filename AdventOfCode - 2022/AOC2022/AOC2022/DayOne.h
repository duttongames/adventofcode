#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> totalCalories;
int highestTotalCalories = 0;
int secondHighestTotalCalories = 0;
int thirdHighestTotalCalories = 0;

//Loads the calories from the txt file and stores the totals in a vector of ints.
void LoadCalories()
{
    //Read the calories file line by line.
	ifstream file("Calories.txt");

    string line;
    int total = 0;

    //Get each calorie value and add them to the total.
    while (getline(file, line))
    {
        if (line != "")
        {
            total += stoi(line);

            //Add the calorie total to the list.
            totalCalories.push_back(total);

            //Update the highest total calories if the total is higher.
            if (total > highestTotalCalories)
            {
                thirdHighestTotalCalories = secondHighestTotalCalories;
                secondHighestTotalCalories = highestTotalCalories;
                highestTotalCalories = total;
            }

            else if (total > secondHighestTotalCalories)
            {
                thirdHighestTotalCalories = secondHighestTotalCalories;
                secondHighestTotalCalories = total;
            }

            else if (total > thirdHighestTotalCalories)
            {
                thirdHighestTotalCalories = total;
            }
        }

        else
        {
            total = 0;
        }
    }
}

//Returns the total calories being carried by the elf with the most calories.
int GetMostCalories()
{
	return highestTotalCalories;
}

//Returns the total calories being carried by the elf with the most, second most and third most calories.
int GetTopThreeCalories()
{
    return highestTotalCalories + secondHighestTotalCalories + thirdHighestTotalCalories;
}