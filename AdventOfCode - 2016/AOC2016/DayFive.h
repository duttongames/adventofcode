#pragma once
#include <iostream>
#include <fstream>
#include <string>

//CREDIT TO STEPHEN BRUMME FOR MD5 HASH LIBRARY: https://github.com/stbrumme/hash-library
#include "md5.h"

using namespace std;

string doorID = "reyedfim";

//Finds the lowest 8 numbers that produces a hash that starts with 5 zeroes and uses the 6th
//character of each hash to determine the password.
string GetDoorPassword(int method)
{
	int currentDigit = 0;

	MD5 currentHash;
	string currentHashString = "";
	string doorPassword = "";
	string password = "--------";
	int passwordCharactersFound = 0;

	//Loop until the password is found.
	while (doorPassword.size() < 8)
	{
		//Increment the current digit to test and create a MD5 Hash from the key.
		currentDigit++;
		currentHashString = currentHash(doorID + to_string(currentDigit));

		//An MD5 hash that starts with 5 zeroes has been found.
		if (currentHashString.size() > 4 && currentHashString[0] == '0' && currentHashString[1] == '0' && currentHashString[2] == '0'
			&& currentHashString[3] == '0' && currentHashString[4] == '0')
		{
			//Add the 6th character of the hash to the password.
			if (method == 1)
			{
				doorPassword += currentHashString[5];
			}

			//Add the seventh character to the position specified by the sixth character
			//if it is within the bounds and hasn't been determined yet.
			else if (currentHashString[5] - '0' >= 0 && currentHashString[5] - '0' < 8 && password[currentHashString[5] - '0'] == '-')
			{
				cout << currentHashString[5] - '0' << endl;
				password[currentHashString[5] - '0'] = currentHashString[6];
				passwordCharactersFound++;

				//Password has been found.
				if (passwordCharactersFound == 8)
				{
					doorPassword = password;
				}
			}
		}
	}

	return doorPassword;
}
