#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Error corrects the message by finding the most common or least common character in each column depending on the method.
string ErrorCorrectMessage(int method)
{
	ifstream messageFile("Message.txt");
	string line;

	vector<string> messageLines;

	//Loop through each line of the message file.
	while (getline(messageFile, line))
	{
		//Add the line to the vector.
		messageLines.push_back(line);
	}

	string errorCorrectedMessage = "";

	//Loop through the message lines column by column.
	for (int i = 0; i < messageLines[0].size(); i++)
	{
		//Count the number of occurences of each letter.
		map<char, int> letterCounts;

		for (int j = 0; j < messageLines.size(); j++)
		{
			letterCounts[messageLines[j][i]]++;
		}

		//Determine which character is the most or least common and add it to the error corrected message.
		char mostCommonChar = ' ';
		int mostOccurences = 0;
		int leastOccurences = INT_MAX;

		map<char, int>::iterator it;

		for (it = letterCounts.begin(); it != letterCounts.end(); it++)
		{
			//Determine which character is the most common.
			if (method == 1)
			{
				if (it->second > mostOccurences)
				{
					mostCommonChar = it->first;
					mostOccurences = it->second;
				}
			}

			else
			{
				if (it->second < leastOccurences)
				{
					mostCommonChar = it->first;
					leastOccurences = it->second;
				}
			}
		}

		errorCorrectedMessage += mostCommonChar;
	}

	messageFile.close();
	return errorCorrectedMessage;
}