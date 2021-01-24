#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Determines which IP addresses support TLS by testing for ABBA(two letters are followed by the reverse of those two letters).
int GetTLSIPs()
{
	ifstream addressFile("IPAddresses.txt");
	string line;

	int validIPs = 0;

	//Loop through each line of the address file.
	while (getline(addressFile, line))
	{
		bool valid = false;
		bool hypernet = false;

		//Loop through the characters of each IP Address and check for ABBA.
		for (int i = 0; i < line.size() - 3; i++)
		{
			//Start and stop reading the hypernet sequence.
			if (line[i] == '[')
			{
				hypernet = true;
			}

			if (line[i] == ']')
			{
				hypernet = false;
			}

			//Check if the next four characters follow ABBA.  The interior characters MUST be different.
			if (line[i] != '[' && line[i + 1] != '[' && line[i + 2] != '[' && line[i + 3] != '['
				&& line[i] != ']' && line[i + 1] != ']' && line[i + 2] != ']' && line[i + 3] != ']')
			{
				if (line[i] == line[i + 3] && line[i + 1] == line[i + 2]
					&& line[i] != line[i + 1])
				{
					//If it is in the hypernet, it is not valid so break.
					if (hypernet)
					{
						valid = false;
						break;
					}

					else
					{
						valid = true;
					}
				}
			}
		}

		//Add the IP to the count if it is valid.
		if (valid)
		{
			validIPs++;
		}
	}

	addressFile.close();
	return validIPs;
}

//Determines which IP addresses support SSL by testing for ABA(two of the same letters with a different letter between them).
int GetSSLIPs()
{
	ifstream addressFile("IPAddresses.txt");
	string line;

	int validIPs = 0;

	//Loop through each line of the address file.
	while (getline(addressFile, line))
	{
		bool valid = false;
		bool hypernet = false;
		string hypernetChars;

		//Stores the ABA corresponding BAB to search for in the hypernet sequences.
		vector<string> byteAllocationBlocks;

		//Loop through the characters of each IP Address and check for ABA.
		for (int i = 0; i < line.size() - 2; i++)
		{
			//Start and stop reading the hypernet sequence.
			if (line[i] == '[')
			{
				hypernet = true;
			}

			else if (line[i] == ']')
			{
				//Break up different hypernet sequences.
				hypernetChars += "   ";
				hypernet = false;
			}

			//Add the hypernet characters to the hypernet vector.
			else if (hypernet)
			{
				hypernetChars += line[i];
			}

			if (line[i] != '[' && line[i + 1] != '[' && line[i + 2] != '['
				&& line[i] != ']' && line[i + 1] != ']' && line[i + 2] != ']')
			{
				//Check if the next three characters follow ABA.  The interior characters MUST be different.
				if (hypernet == false)
				{
					if (line[i] == line[i + 2] && line[i] != line[i + 1])
					{
						//Add the ABA's corresponding BAB to the vector.
						string bab = "";
						bab += line[i + 1];
						bab += line[i];
						bab += line[i + 1];
						byteAllocationBlocks.push_back(bab);
					}
				}
			}
		}

		//Loop through all the hypernet characters and check if any contain a valid BAB.
		for (int i = 0; i < hypernetChars.size() - 2; i++)
		{
			//Three spaces break up different hypernet sequences.
			if (hypernetChars[i] != ' ' && hypernetChars[i + 1] != ' ' && hypernetChars[i + 2] != ' ')
			{
				string currentCharsToCheck = "";
				currentCharsToCheck += hypernetChars[i];
				currentCharsToCheck += hypernetChars[i + 1];
				currentCharsToCheck += hypernetChars[i + 2];

				for (int j = 0; j < byteAllocationBlocks.size(); j++)
				{
					//If it is a valid BAB, the IP supports SSL so break the loop.
					if (currentCharsToCheck == byteAllocationBlocks[j])
					{
						valid = true;
						break;
					}
				}
			}
		}

		//Add the IP to the count if it is valid.
		if (valid)
		{
			validIPs++;
		}
	}

	addressFile.close();
	return validIPs;
}