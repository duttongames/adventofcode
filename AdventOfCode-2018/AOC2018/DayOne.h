#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

//Get the final resulting frequency after all the frequency changes.
int GetFinalFrequency()
{
	int frequency = 0;
	int finalFrequency = 0;
	int loops = 0;
	bool duplicateFrequency = false;

	//Stores whether a frequency has been seen before.
	map<int, bool> frequenciesSeen;
	frequenciesSeen[frequency] = true;

	//Loop through each frequency change.
	while (duplicateFrequency == false)
	{
		ifstream frequencyFile("Frequency.txt");
		string line;

		while (getline(frequencyFile, line))
		{
			frequency += stoi(line);

			//If the frequency has been seen before, output it as the first duplicate frequency.
			if (frequenciesSeen[frequency] && duplicateFrequency == false)
			{
				cout << "The first duplicate frequency is: " + to_string(frequency) << endl;
				duplicateFrequency = true;
			}

			//Otherwise set the frequency as seen.
			else
			{
				frequenciesSeen[frequency] = true;
			}
		}

		//Save the final frequency.
		if (loops == 0)
		{
			finalFrequency = frequency;
		}

		loops++;

		frequencyFile.close();
	}

	return finalFrequency;
}