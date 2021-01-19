#pragma once
#include <iostream>
#include <fstream>
#include <string>

//CREDIT TO STEPHEN BRUMME FOR MD5 HASH LIBRARY: https://github.com/stbrumme/hash-library
#include "md5.h"

using namespace std;

string hashKey = "yzbqklnj";

//Finds and returns the lowest digit that produces a hash that starts with 5 or 6 zeroes depending on the method.
int FindSuitableHash(int method)
{
	int currentDigit = 0;

	MD5 currentHash;
	string currentHashString = "";
	bool suitableHashFound = false;

	//Loop until a suitable hash is found.
	while (suitableHashFound == false)
	{
		//Increment the current digit to test and create a MD5 Hash from the key.
		currentDigit++;
		currentHashString = currentHash(hashKey + to_string(currentDigit));

		//Find the first MD5 Hash that starts with 5 zeroes.
		if (method == 1)
		{
			if (currentHashString.size() > 4 && currentHashString[0] == '0' && currentHashString[1] == '0' && currentHashString[2] == '0'
				&& currentHashString[3] == '0' && currentHashString[4] == '0')
			{
				suitableHashFound = true;
			}
		}

		//Find the first MD5 Hash that starts with 6 zeroes.
		else
		{
			if (currentHashString.size() > 5 && currentHashString[0] == '0' && currentHashString[1] == '0' && currentHashString[2] == '0'
				&& currentHashString[3] == '0' && currentHashString[4] == '0' && currentHashString[5] == '0')
			{
				suitableHashFound = true;
			}
		}
	}

	return currentDigit;
}