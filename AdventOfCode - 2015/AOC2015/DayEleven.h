#pragma once
#include <iostream>
#include <string>

using namespace std;

//Determines what Santa's next password should be.
string GetNextPassword(string startingPassword)
{
	string currentPassword = startingPassword;

	bool validPassword = false;

	while (validPassword == false)
	{
		validPassword = true;

		//Increment the password.
		for (int i = currentPassword.size() - 1; i >= 0; --i)
		{
			//Change the character to 'a' if it is 'z' and move onto the previous character.
			if (currentPassword[i] == 'z')
			{
				currentPassword[i] = 97;
			}

			else
			{
				currentPassword[i]++;
				break;
			}
		}

		bool hasStraight = false;
		bool hasTwoPairs = false;
		string firstPair = "";

		//Loop through the current password and check it fulfils all the password conditions.
		for (int i = 0; i < currentPassword.size(); ++i)
		{
			//Check the password contains a straight of three letters.
			if (hasStraight == false && i < currentPassword.size() - 2)
			{
				if (currentPassword[i + 1] == currentPassword[i] + 1 && currentPassword[i + 2] == currentPassword[i] + 2)
				{
					hasStraight = true;
				}
			}

			//Check the password does not contain an 'i', 'o' or 'l'.
			if (currentPassword[i] == 'i' || currentPassword[i] == 'o' || currentPassword[i] == 'l')
			{
				validPassword = false;
				break;
			}

			//Check the password contains two different repeating pairs.
			if (i < currentPassword.size() - 1)
			{
				//If the current character and next character are a pair...
				if (currentPassword[i] == currentPassword[i + 1])
				{
					//If there is no first pair yet, save the first pair.
					if (firstPair == "")
					{
						firstPair += currentPassword[i];
						firstPair += currentPassword[i + 1];
					}

					//If the pair is not the same as the first pair, there are two different repeating pairs.
					else if (currentPassword[i] != firstPair[0])
					{
						hasTwoPairs = true;
					}
				}
			}

			//If the end has been reached...
			if (i == currentPassword.size() - 1)
			{
				//If there is no straight, the password is not valid.
				if (!hasStraight)
				{
					validPassword = false;
				}

				//If there are not two different repeating pairs, the password is not valid.
				if (!hasTwoPairs)
				{
					validPassword = false;
				}
			}
		}
	}

	//Return the next password.
	return currentPassword;
}