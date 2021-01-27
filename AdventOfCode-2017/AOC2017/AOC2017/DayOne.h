#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//Goes through the file and adds together all the digits that match the next digit in the list or the
//digit halfways round the list depending on the method.
int SolveCaptcha(int method)
{
	int sum = 0;
	int sumTwo = 0;
	char firstDigit = ' ';

	vector<int> digits;

	ifstream digitsFile("Digits.txt");
	string line;

	//Loop through each line of digits.
	while (getline(digitsFile, line))
	{
		//Loop through each digit on the line.
		for (int i = 0; i < line.size(); i++)
		{
			if (method == 2)
			{
				digits.push_back(line[i] - '0');
			}

			else
			{
				//Compare the last digit against the first.
				if (i == line.size() - 1)
				{
					if (line[i] == firstDigit)
					{
						sum += (line[i] - '0');
					}
				}

				//Compare the digit against the next digit.
				else
				{
					//Store the first digit.
					if (firstDigit == ' ')
					{
						firstDigit = line[i];
					}

					if (line[i] == line[i + 1])
					{
						sum += (line[i] - '0');
					}
				}
			}
		}
	}

	//Use the second method to compare the digit halfway around the list.
	if (method == 2)
	{
		//The steps to move are half the list's size.
		int steps = digits.size() / 2;
		int counter = 0;

		//Loop through each digits.
		for (int i = 0; i < digits.size(); i++)
		{
			counter = i;

			//Loop until finding the digit halfway around the list.
			for (int j = 0; j < steps; j++)
			{
				if (counter > digits.size() - 2)
				{
					counter = 0;
				}

				else
				{
					counter++;
				}
			}

			//If the digits are the same add the first digit to the sum.
			if (digits[i] == digits[counter])
			{
				sum += digits[i];
			}
		}
	}

	return sum;
}