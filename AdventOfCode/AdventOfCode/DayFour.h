#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void FindWord(string lineToSearch, vector<int> &fields)
{
	string word = "";
	string foundWord = "";

	for (int i = 0; i < lineToSearch.size(); i++)
	{
		if (lineToSearch[i] != ' ' && lineToSearch[i] != ':')
		{
			word += lineToSearch[i];
		}

		if(lineToSearch[i] == ' ' || i == lineToSearch.size() - 1)
		{
			if (foundWord == "byr")
			{
				if (word.size() == 4 && stoi(word) >= 1920 && stoi(word) <= 2002)
				{
					fields[0] = 1;
				}
			}

			if (foundWord == "iyr")
			{
				if (word.size() == 4 && stoi(word) >= 2010 && stoi(word) <= 2020)
				{
					fields[1] = 1;
				}
			}

			if (foundWord == "eyr")
			{
				if (word.size() == 4 && stoi(word) >= 2020 && stoi(word) <= 2030)
				{
					fields[2] = 1;
				}
			}

			if (foundWord == "hgt")
			{
				if (word.find("cm") != string::npos && word.size() > 2)
				{
					string size = "";

					size += word[0];
					size += word[1];
					size += word[2];

					if (size.find_first_not_of("0123456789") == string::npos)
					{
						if (stoi(size) >= 150 && stoi(size) <= 193)
						{
							fields[3] = 1;
						}
					}
				}

				if (word.find("in") != string::npos && word.size() > 1)
				{
					string size = "";

					size += word[0];
					size += word[1];

					if (size.find_first_not_of("0123456789") == string::npos)
					{
						if (stoi(size) >= 59 && stoi(size) <= 76)
						{
							fields[3] = 1;
						}
					}
				}
			}

			if (foundWord == "hcl")
			{
				if (word.size() == 7 && word[0] == '#')
				{
					string colour = word.erase(0, 1);

					if (colour.find_first_not_of("0123456789abcdef") == string::npos)
					{
						fields[4] = 1;
					}
				}
			}

			if (foundWord == "ecl")
			{
				if (word == "amb" || word == "blu" || word == "brn" || word == "gry"
					|| word == "grn" || word == "hzl" || word == "oth")
				{
					fields[5] = 1;
				}
			}

			if (foundWord == "pid")
			{
				if (word.size() == 9 && word.find_first_not_of("0123456789") == string::npos)
				{
					fields[6] = 1;
				}
			}

			foundWord = "";
			word = "";
		}

		if (word == "byr" || word == "iyr" || word == "eyr" || word == "hgt" || word == "hcl"
			|| word == "ecl" || word == "pid")
		{
			foundWord = word;
			word = "";
		}
	}
}

int CheckPassports()
{
	string line;

	ifstream passports("Passports.txt");

	bool validated = false;
	int validPassports = 0;
	vector<int> fieldsPresent = { 0, 0, 0, 0, 0, 0, 0, 0 };

	while (getline(passports, line))
	{
		if (validated == false)
		{
			FindWord(line, fieldsPresent);

			if (fieldsPresent[0] == 1 && fieldsPresent[1] == 1 && fieldsPresent[2] == 1 && fieldsPresent[3] == 1
				&& fieldsPresent[4] == 1 && fieldsPresent[5] == 1 && fieldsPresent[6] == 1)
			{
				validated = true;
				validPassports++;
			}
		}

		if (line.find_first_not_of(' ') == string::npos)
		{
			validated = false;

			for (int i = 0; i < fieldsPresent.size(); i++)
			{
				fieldsPresent[i] = 0;
			}
		}
	}

	return validPassports;
}