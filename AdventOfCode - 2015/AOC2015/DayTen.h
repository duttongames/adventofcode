#pragma once
#include <iostream>
#include <string>

using namespace std;

//Determines the result of playing Look and Say x number of times with y starting number.
string LookAndSay(string startingNumber, int iterations)
{
	string currentNumber = startingNumber;

	//Play the game in a loop for the specified number of iterations.
	for (int i = 0; i < iterations; ++i)
	{
		char currentDigit = currentNumber[0];
		int digitCount = 1;
		string nextNumber = "";
		string currentDigitStr = "";
		currentDigitStr += currentDigit;

		//Loop through the current number and determine the next number.
		for (int j = 1; j < currentNumber.size(); ++j)
		{
			//Increase the digit count and add to the current digit string if the current digit is the same as the previous digit.
			if (currentNumber[j] == currentDigit)
			{
				currentDigitStr += currentDigit;
				digitCount++;

				//If at the end of the number, add the digit count and current digit to the next number.
				if (j == currentNumber.size() - 1)
				{
					nextNumber += to_string(digitCount);
					nextNumber += currentDigit;
				}
			}

			//If it is a different digit, add the digit count and the current digit to the next number.
			else
			{
				nextNumber += to_string(digitCount);
				nextNumber += currentDigit;
				currentDigitStr = "";
				currentDigit = currentNumber[j];
				currentDigitStr += currentDigit;
				digitCount = 1;

				//If at the end of the number, add the digit count and current digit to the next number.
				if (j == currentNumber.size() - 1)
				{
					nextNumber += to_string(digitCount);
					nextNumber += currentDigit;
				}
			}
		}

		if (currentNumber.size() == 1)
		{
			nextNumber = "1";
			nextNumber += currentDigit;
		}

		currentNumber = nextNumber;
	}

	//Return the result.
	return currentNumber;
}