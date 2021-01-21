#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char firstKeypad[5][5]{ ' ', ' ', ' ', ' ', ' ',
					    ' ', '1', '2', '3', ' ',
					    ' ', '4', '5', '6', ' ',
					    ' ', '7', '8', '9', ' ',
						' ', ' ', ' ', ' ', ' ', };

char secondKeypad[5][5] = { ' ', ' ', '1', ' ', ' ',
						 ' ', '2', '3', '4', ' ',
						 '5', '6', '7', '8', '9',
						 ' ', 'A', 'B', 'C', ' ',
						 ' ', ' ', 'D', ' ', ' ' };

//Follows the instructions and returns the Bathroom Code for the keypad.
string GetBathroomCode(char keypad[5][5])
{
	ifstream codeFile("CodeInstructions.txt");
	string line;
	string bathroomCode = "";
	
	//Start on the middle digit: 5.
	int row = 2;
	int column = 2;

	//Loop through the instructions for each digit of the code.
	while (getline(codeFile, line))
	{
		//Loop through the line and follow each instruction to determine what the next digit of the code is.
		for (int i = 0; i < line.size(); i++)
		{
			//Determine where to move next.
			switch (line[i])
			{
				//Move up one.
				case 'U':
					if (row > 0)
					{
						if (keypad[row - 1][column] != ' ')
						{
							row--;
						}
					}
					break;

				//Move down one.
				case 'D':
					if (row < 4)
					{
						if (keypad[row + 1][column] != ' ')
						{
							row++;
						}
					}
					break;

				//Move left one.
				case 'L':
					if (column > 0)
					{
						if (keypad[row][column - 1] != ' ')
						{
							column--;
						}
					}
					break;

				//Move right one.
				case 'R':
					if (column < 4)
					{
						if (keypad[row][column + 1] != ' ')
						{
							column++;
						}
					}
					break;
			}
		}

		//Add the next digit of the bathroom code.
		bathroomCode += keypad[row][column];
	}

	codeFile.close();
	return bathroomCode;
}