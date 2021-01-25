#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Executes all the screen instructions and returns the number of pixels that should be lit.
int GetPixels()
{
	ifstream screenFile("ScreenInstructions.txt");
	string line;

	//The screen is 50 pixels wide and 6 pixels tall.
	char screen[50][6];

	//Turn all the pixels off.
	for (int i = 0; i < sizeof(screen) / sizeof(screen[0]); i++)
	{
		for (int j = 0; j < sizeof(screen[i]) / sizeof(screen[i][0]); j++)
		{
			screen[i][j] = '.';
		}
	}

	//Loop through each line of the screen instructions file.
	while (getline(screenFile, line))
	{
		string command = "";
		string valueOne = "";
		string valueTwo = "";
		bool readValueTwo = false;

		//Read each character of the line to determine what command to execute.
		for (int i = 0; i < line.size(); i++)
		{
			//Add to the command string until a valid command is determined.
			if (command != "rect" && command != "rotate row" && command != "rotate column")
			{
				command += line[i];
			}

			//Determine the second value.
			if (isdigit(line[i]) && readValueTwo)
			{
				valueTwo += line[i];
			}

			//Determine the first value.
			else if (isdigit(line[i]))
			{
				valueOne += line[i];
			}

			//Read the second value instead of the first.
			if (line[i] == ' ' || line[i] == 'x')
			{
				if (valueOne.size() > 0)
				{
					readValueTwo = true;
				}
			}
		}

		//Turn on all pixels in a rectangle at the top-left of the screen. '#' represents a pixel.
		if (command == "rect")
		{
			for (int i = 0; i < stoi(valueOne); i++)
			{
				for (int j = 0; j < stoi(valueTwo); j++)
				{
					screen[i][j] = '#';
				}
			}
		}

		//Shifts all of the pixels in the specified column down the specified number of times.
		char next = '.';

		if (command == "rotate column")
		{
			for (int i = 0; i < stoi(valueTwo); i++)
			{
				for (int j = 0; j < 6; j++)
				{
					char temp = screen[stoi(valueOne)][j];
					screen[stoi(valueOne)][j] = next;
					next = temp;
				}

				screen[stoi(valueOne)][0] = next;
			}
		}

		//Shifts all of the pixels in the specified row right the specified number of times.
		next = '.';

		if (command == "rotate row")
		{
			for (int i = 0; i < stoi(valueTwo); i++)
			{
				for (int j = 0; j < 50; j++)
				{
					char temp = screen[j][stoi(valueOne)];
					screen[j][stoi(valueOne)] = next;
					next = temp;
				}

				screen[0][stoi(valueOne)] = next;
			}
		}
	}

	//Count the number of pixels on the screen and output the final pixel formation.
	int pixels = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			//A pixel is represented by a '#'.
			if (screen[i][j] == '#')
			{
				pixels++;
			}

			cout << screen[j][i];
		}

		cout << endl;
	}

	screenFile.close();
	return pixels;
}