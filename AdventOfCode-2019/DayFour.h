#pragma once
#include <iostream>
#include <string>

using namespace std;

//Returns the number of passwords that fulfil the criteria within a certain range of numbers.
int GetValidPasswords(int startingNumber, int endingNumber, int method)
{
	int validPasswords = 0;

	//Loop through all the numbers within the given range.
	for (int i = startingNumber; i <= endingNumber; ++i)
	{
		string strNumber = to_string(i);
		int previousDigit = strNumber[0] - '0';
		bool adjacent = false;
		bool decrease = false;

		//Loop through each digit of the number.
		for (int j = 1; j < 6; ++j)
		{
			//Check if two adjacent digits are the same.
			if (!adjacent && strNumber[j] == strNumber[j - 1])
			{
				if (method == 0)
				{
					adjacent = true;
				}

				//If using the second method, check the two adjacent digits are not part of a larger group.
				if (method == 1)
				{
					int checksPassed = 0;

					//Check the digit two digits to the left.
					if (j == 1 || strNumber[j - 2] != strNumber[j])
					{
						checksPassed++;
					}

					//Check the digit one digit to the right.
					if (j == 5 || strNumber[j + 1] != strNumber[j])
					{
						checksPassed++;
					}

					//If it passes both checks, it is not part of a larger group and therefore valid.
					if (checksPassed == 2)
					{
						adjacent = true;
					}
				}
			}

			//Check the previous digit is less than or the same as the current digit.
			if (previousDigit > strNumber[j] - '0')
			{
				decrease = true;
				j = 5;
			}

			previousDigit = strNumber[j] - '0';
		}

		//If there are two adjacent digits and the digits never decrease, add to the valid passwords count.
		if (adjacent && !decrease)
		{
			validPasswords++;
		}
	}

	return validPasswords;
}