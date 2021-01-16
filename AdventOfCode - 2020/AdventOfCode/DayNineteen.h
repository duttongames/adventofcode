#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

map<string, vector<vector<string>>> rules;
vector<string> messages;
vector<string> validMessages;

//Reads the rules and messages for Day 19.
void ReadRulesAndMessages()
{
	string line;

	ifstream messageRules("Rules.txt");

	//Get the input from the txt file.
	while (getline(messageRules, line))
	{
		vector<string> currentRules;
		string currentWord = "";
		string rule = "";

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != ' ' && line[i] != ':' && line[i] != '|')
			{
				currentWord += line[i];
			}

			else
			{
				if (line[i] == '|' || i == line.size() - 1)
				{
					rules[rule].push_back(currentRules);
					currentRules.clear();
				}

				else if (line[i] == ':')
				{
					rule = currentWord;
				}

				else if (currentWord != "")
				{
					currentRules.push_back(currentWord);
				}

				currentWord = "";
			}

			if (i == line.size() - 1)
			{
				if (currentWord[0] == '"')
				{
					currentWord = currentWord[1];
				}

				currentRules.push_back(currentWord);
				rules[rule].push_back(currentRules);
				currentRules.clear();
			}
		}
	}

	ifstream msgs("Messages.txt");

	while (getline(msgs, line))
	{
		messages.push_back(line);
	}

	map<string, vector<vector<string>>>::iterator it;

	for (it = rules.begin(); it != rules.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			for (int j = 0; j < it->second[i].size(); j++)
			{
				//cout << to_string(it->first) + ": " + it->second[i][j] << endl;
			}
		}
	}
}

//Recursive function that returns all the valid messages based on the rules.
string GetValidMessages(string ruleNumber, string currentMessage)
{
	if (ruleNumber == "a" || ruleNumber == "b")
	{
		currentMessage += ruleNumber;
	}

	else
	{
		for (int j = 0; j < rules[ruleNumber][0].size(); j++)
		{
			currentMessage = GetValidMessages(rules[ruleNumber][0][j], currentMessage);
		}
	}

	if (ruleNumber == "0")
	{
		validMessages.push_back(currentMessage);
	}

	return currentMessage;
}