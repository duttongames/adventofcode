#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int CheckPasswords(int methodToUse)
{
	int validPasswords = 0;

	string line;

	ifstream passwords("Passwords.txt");

	while (getline(passwords, line))
	{
		int min = 0;
		int max = 0;
		char letter = ' ';
		string currentValue;
		string currentPassword;

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == '-')
			{
				min = stoi(currentValue);
				currentValue = "";
			}

			else if (line[i] == ' ' && max == 0)
			{
				max = stoi(currentValue);
				currentValue = "";
			}

			else if (line[i] == ':')
			{
				letter = currentValue[0];
				currentValue = "";
			}
			
			else if (line[i] != ' ')
			{
				currentValue += line[i];
			}

			if (i == line.size() - 1)
			{
				currentPassword = currentValue;
			}
		}

		//Use the first method.
		if (methodToUse == 1)
		{
			int letterCount = 0;

			for (int i = 0; i < currentPassword.size(); i++)
			{
				if (currentPassword[i] == letter)
				{
					letterCount++;
				}
			}

			if (letterCount >= min && letterCount <= max)
			{
				validPasswords++;
			}
		}

		//Use the second method.
		if (methodToUse == 2)
		{
			if (currentPassword[min - 1] == letter || currentPassword[max - 1] == letter)
			{
				if (currentPassword[min - 1] == letter && currentPassword[max - 1] == letter)
				{

				}

				else
				{
					validPasswords++;
				}
			}
		}
	}

	return validPasswords;
}