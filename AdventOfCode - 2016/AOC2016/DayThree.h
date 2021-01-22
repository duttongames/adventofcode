#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Gets how many triangles in the file are possible.
int GetPossibleTriangles(int method)
{
	ifstream triangleFile("Triangles.txt");
	string line;
	
	int possibleTriangles = 0;

	vector<vector<int>> triangles;

	//Loop through each triangle.
	while (getline(triangleFile, line))
	{
		int sideOne = 0;
		int sideTwo = 0;
		int sideThree = 0;

		string currentSide = "";
		
		vector<int> rowSides;

		//Loop through the line and get each side.
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ' || i == line.size() - 1)
			{
				if (i == line.size() - 1)
				{
					currentSide += line[i];
				}

				//Parse each side.
				if (currentSide != "")
				{
					rowSides.push_back(stoi(currentSide));

					if (sideOne == 0)
					{
						sideOne = stoi(currentSide);
					}

					else if (sideTwo == 0)
					{
						sideTwo = stoi(currentSide);
					}

					else
					{
						sideThree = stoi(currentSide);
					}
				}
				currentSide = "";
			}

			else
			{
				currentSide += line[i];
			}
		}

		if (method == 1)
		{
			//Determine if the triangle is possible by adding its sides.
			if (sideOne + sideThree > sideTwo && sideTwo + sideOne > sideThree && sideTwo + sideThree > sideOne)
			{
				possibleTriangles++;
			}
		}

		if (method == 2)
		{
			triangles.push_back(rowSides);
		}
	}

	//Count the sides of the triangles by columns for the second method.
	if (method == 2)
	{
		int sideOne = 0;
		int sideTwo = 0;
		int sideThree = 0;

		int sideCounter = 0;

		//Loop through all the triangle sides column first.
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < triangles.size(); j++)
			{
				//Get the first side.
				if (sideCounter == 0)
				{
					sideOne = triangles[j][i];
					sideCounter++;
				}

				//Get the second side.
				else if (sideCounter == 1)
				{
					sideTwo = triangles[j][i];
					sideCounter++;
				}

				//Get the third side.
				else if (sideCounter == 2)
				{
					sideThree = triangles[j][i];

					//Determine if the triangle is possible by adding its sides.
					if (sideOne + sideThree > sideTwo && sideTwo + sideOne > sideThree && sideTwo + sideThree > sideOne)
					{
						possibleTriangles++;
					}

					sideCounter = 0;
				}
			}
		}
	}

	return possibleTriangles;
}