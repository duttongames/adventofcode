#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int CountAnswers()
{
	string line;

	ifstream answers("QuestionAnswers.txt");

	int yesNumber = 0;
	int personNumber = 0;

	int questions[26] = { };
	int questionNumbers[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	//Loop through the lines of the txt.
	while (getline(answers, line))
	{
		//Clear the answered questions if the line is blank/it's a new group.
		if (line == "")
		{
			//Check if the amount of times the question was answered 'yes' is the same as the number of people in the group.
			for (int i = 0; i < sizeof(questions) / sizeof(*questions); i++)
			{
				if (questions[i] == personNumber)
				{
					yesNumber++;
				}

				questions[i] = 0;
			}

			personNumber = 0;
		}

		else
		{
			//Loop through the letters of the line.
			for (int i = 0; i < line.size(); i++)
			{
				//Increase the number of times a specific question has been answered 'yes'.
				for (int j = 0; j < sizeof(questionNumbers) / sizeof(*questionNumbers); j++)
				{
					if (questionNumbers[j] == line[i])
					{
						questions[j]++;
					}
				}
			}

			personNumber++;
		}
	}

	//Determine the amount of questions answered 'yes' by everyone in the group for the last group.
	for (int i = 0; i < sizeof(questions) / sizeof(*questions); i++)
	{
		if (questions[i] == personNumber)
		{
			yesNumber++;
		}

		questions[i] = 0;
	}

	personNumber = 0;

	//Return the sum of questions that have been answered 'yes'.
	return yesNumber;
}