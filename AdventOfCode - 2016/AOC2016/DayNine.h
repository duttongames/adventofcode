#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Decompresses the file.
string DecompressFile()
{
	ifstream compressedFile("CompressedFile.txt");
	string line;

	string decompressedFile = "";
	bool decompressing = false;
	bool readingMarker = false;
	bool repeatNumber = false;

	//Loop through each line of the compressed file.
	while (getline(compressedFile, line))
	{
		string charsToRead = "";
		string timesToRepeat = "";
		string charsToRepeat = "";
		int charsCounted = 0;

		//Loop through each character on the line.
		for (int i = 0; i < line.size(); i++)
		{
			if (!decompressing)
			{
				//Read the contents of the marker.
				if (readingMarker)
				{
					if (isdigit(line[i]))
					{
						if (repeatNumber == false)
						{
							charsToRead += line[i];
						}

						else
						{
							timesToRepeat += line[i];
						}
					}

					if (line[i] == 'x')
					{
						repeatNumber = true;
					}
				}

				else if (line[i] != '(' && line[i] != ')')
				{
					decompressedFile += line[i];
				}

				//Start and stop reading the marker.
				if (line[i] == '(')
				{
					readingMarker = true;
				}

				if (line[i] == ')')
				{
					decompressing = true;
					readingMarker = false;
				}
			}

			else
			{
				//Read the characters to repeat.
				if (charsCounted < stoi(charsToRead))
				{
					charsToRepeat += line[i];
					charsCounted++;
				}

				//Decompress the characters by repeating them the specified number of times.
				if (charsCounted == stoi(charsToRead))
				{
					for (int i = 0; i < stoi(timesToRepeat); i++)
					{
						decompressedFile += charsToRepeat;
					}

					charsToRead = "";
					timesToRepeat = "";
					charsToRepeat = "";
					decompressing = false;
					repeatNumber = false;
					charsCounted = 0;
				}
			}
		}
	}

	compressedFile.close();
	return decompressedFile;
}