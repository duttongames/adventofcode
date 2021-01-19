#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Finds the number of string literal characters minus the number of characters in memory in the file.
int GetNumberOfCharacters()
{
	ifstream listFile("List.txt");
	string line;

	int literalChars = 0;
	int memoryChars = 0;
	int charsToSkip = 0;

	//Loop through each string on Santa's list.
	while (getline(listFile, line))
	{
		bool countMemoryChars = false;

		//Loop through the line.
		for (int i = 0; i < line.size(); i++)
		{
			//Count the number of string characters.
			literalChars++;

			//Count the number of memory characters.
			if (countMemoryChars && line[i] != '"' && charsToSkip == 0)
			{
				memoryChars++;

				if (line[i] == '\\' && line[i + 1] == 'x')
				{
					charsToSkip += 3;
				}

				if (line[i] == '\\' && line[i + 1] == '\\')
				{
					charsToSkip++;
				}
			}

			else if (charsToSkip > 0)
			{
				charsToSkip--;
			}

			if (line[i] == '"')
			{
				countMemoryChars = true;
			}
		}
	}

	return literalChars - memoryChars;
}