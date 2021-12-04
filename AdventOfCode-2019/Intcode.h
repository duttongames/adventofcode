#pragma once
#include <map>

map<int, int> addresses;

//Performs the intcode operation specified.
int IntcodeOps(int operation, int mode, int firstValue, int secondValue)
{
	switch (operation)
	{
		//Add two values.
		case 1:
			return firstValue + secondValue;
				break;

		//Multiply two values.
		case 2:
			return firstValue * secondValue;
			break;

		//Save the given input to the given address/position.
		case 3:
			addresses[firstValue] = secondValue;
			break;

		//Return the value at the given address/position.
		case 4:
			return addresses[firstValue];
			break;
	}
}