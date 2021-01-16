#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Read the floor instructions.
int ReadFloors(int startingFloor)
{
	ifstream floorFile("Floors.txt");
	string line;

	int position = 1;
	bool enteredBasement = false;

	//Loop through each line of instructions.
	while (getline(floorFile, line)) 
	{
		for (int i = 0; i < line.size(); i++)
		{
			//Increase the starting floor when encountering a (.
			if (line[i] == '(')
			{
				startingFloor++;
			}

			//Decrease the starting floor when encountering a ).
			if (line[i] == ')')
			{
				startingFloor--;
			}

			//Detect when the basement is entered.
			if (enteredBasement == false && startingFloor == -1)
			{
				cout << "Basement entered at Position " + to_string(position) << endl;
				enteredBasement = true;
			}

			position++;
		}
	}

	floorFile.close();

	return startingFloor;
}