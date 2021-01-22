#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Determines which rooms are real and gets the sum of the sector ID's of all the real rooms.
int GetValidRooms()
{
	ifstream roomFile("Rooms.txt");
	string line;

	int sectorSum = 0;

	//Loop through each room ID.
	while (getline(roomFile, line))
	{
		vector<char> characters;
		vector<int> characterCounts;
		string sectorID;
		string checksum;
		bool readingChecksum = false;

		//Loop through each character of the room ID. The last character can be ignored.
		for (int i = 0; i < line.size() - 1; i++)
		{
			if (readingChecksum == false)
			{
				//Start reading the checksum.
				if (line[i] == '[')
				{
					readingChecksum = true;
				}

				else
				{
					//Read the sector ID.
					if (isdigit(line[i]))
					{
						sectorID += line[i];
					}

					//Read the encrypted room name and increment the number of character appearances.
					else if (line[i] != '-')
					{
						vector<char>::iterator characterPosition = find(characters.begin(), characters.end(), line[i]);

						if (characterPosition == characters.end())
						{
							characters.push_back(line[i]);
							characterCounts.push_back(1);
						}

						else
						{
							characterCounts[distance(characters.begin(), characterPosition)]++;
						}
					}
				}
			}

			//Read the checksum.
			else
			{
				checksum += line[i];
			}
		}

		//Get the five most common words using bubble sort.
		bool sorted = false;

		while (sorted == false)
		{
			sorted = true;

			for (int i = 1; i < characterCounts.size(); i++)
			{
				//Swap the characters if they have the same count but are not in alpabetical order.
				if (characterCounts[i] == characterCounts[i - 1])
				{
					if (characters[i] < characters[i - 1])
					{
						char temp = characters[i - 1];
						characters[i - 1] = characters[i];
						characters[i] = temp;

						int numTemp = characterCounts[i - 1];
						characterCounts[i - 1] = characterCounts[i];
						characterCounts[i] = numTemp;

						sorted = false;
					}
				}

				//Swap the characters if the current character has a larger count.
				else if (characterCounts[i] > characterCounts[i - 1])
				{
					char temp = characters[i - 1];
					characters[i - 1] = characters[i];
					characters[i] = temp;

					int numTemp = characterCounts[i - 1];
					characterCounts[i - 1] = characterCounts[i];
					characterCounts[i] = numTemp;

					sorted = false;
				}
			}
		}

		//Add to the sectorSum total if the first five characters of the vector are the same as the checksum.
		string mostCommon = "";
		mostCommon += characters[0];
		mostCommon += characters[1];
		mostCommon += characters[2];
		mostCommon += characters[3];
		mostCommon += characters[4];
	
		if (mostCommon == checksum)
		{
			sectorSum += stoi(sectorID);
		}
	}

	return sectorSum;
}

//Decrypts each room until finding the specified room and returns that room's sector ID.
int DecryptRooms(string roomToFind)
{
	ifstream roomFile("Rooms.txt");
	string line;

	//Loop through each room ID.
	while (getline(roomFile, line))
	{
		string roomName;
		string sectorID;

		for (int i = 0; i < line.size() - 7; i++)
		{
			//Read the sector ID.
			if (isdigit(line[i]))
			{
				sectorID += line[i];
			}

			//Read the encrypted room name.
			else
			{
				if (line[i] == '-')
				{
					roomName += ' ';
				}

				else
				{
					roomName += line[i];
				}
			}
		}

		//Remove space from the end.
		roomName = roomName.substr(0, roomName.size() - 1);

		//Rotate each letter of the room name through the alphabet a number of times equal to the sectorID to decrypt it.
		for (int i = 0; i < roomName.size(); i++)
		{
			if (roomName[i] != ' ')
			{
				for (int j = 0; j < stoi(sectorID); j++)
				{
					if (roomName[i] >= 122)
					{
						roomName[i] = 97;
					}

					else
					{
						roomName[i]++;
					}
				}
			}
		}

		//Return the decrypted version of the name upon finding the correct name.
		if (roomName == roomToFind)
		{
			return stoi(sectorID);
		}
	}

	return 0;
}