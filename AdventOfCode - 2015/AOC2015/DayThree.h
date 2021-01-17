#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Gets the amount of houses that have received at least one present.
int GetDeliveredHouses()
{
	ifstream directionsFile("Directions.txt");
	string line;

	//Create the house grid.
	map<vector<int>, int> houses;
	int totalHousesDeliveredTo = 1;

	int currentHouseX = 500;
	int currentHouseY = 500;
	vector<int> currentPosition = { currentHouseX, currentHouseY }; //The first element represents x and the second y.

	int roboHouseX = 500;
	int roboHouseY = 500;
	vector<int> currentRoboPosition = { roboHouseX, roboHouseY }; //The first element represents x and the second y.

	//Set the starting house as delivered to once.
	houses[currentPosition]+= 2;

	bool moveRobo = false;

	//Loop through each line.
	while (getline(directionsFile, line))
	{
		//Loop through each character on the line.
		for (int i = 0; i < line.size(); i++)
		{
			//Go in the direction indicated by the current arrow character.
			switch (line[i])
			{
				case '^':
					if (moveRobo)
					{
						roboHouseY--;
					}

					else
					{
						currentHouseY--;
					}
					break;

				case 'v':
					if (moveRobo)
					{
						roboHouseY++;
					}

					else
					{
						currentHouseY++;
					}
					break;

				case '>':
					if (moveRobo)
					{
						roboHouseX++;
					}

					else
					{
						currentHouseX++;
					}
					break;

				case '<':
					if (moveRobo)
					{
						roboHouseX--;
					}

					else
					{
						currentHouseX--;
					}
					break;
			}

			//Update the position.
			currentPosition[0] = currentHouseX;
			currentPosition[1] = currentHouseY;

			currentRoboPosition[0] = roboHouseX;
			currentRoboPosition[1] = roboHouseY;

			//Increment the total if the house hasn't been delivered to before.
			if (moveRobo == false)
			{
				if (houses[currentPosition] <= 0)
				{
					totalHousesDeliveredTo++;
				}

				//Increment the amount of times this house has been delivered to.
				houses[currentPosition]++;
			}

			if (moveRobo)
			{
				if (houses[currentRoboPosition] <= 0)
				{
					totalHousesDeliveredTo++;
				}

				//Increment the amount of times this house has been delivered to.
				houses[currentRoboPosition]++;
			}

			moveRobo = !moveRobo;
		}
	}

	return totalHousesDeliveredTo;
}