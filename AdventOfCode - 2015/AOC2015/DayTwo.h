#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Gets the amount of wrapping paper needed in feet.
long GetFeetNeeded()
{
	ifstream dimensionsFile("Dimensions.txt");
	string line;

	long totalFeet = 0;
	long totalRibbonFeet = 0;

	//Loop through each line/present.
	while (getline(dimensionsFile, line))
	{
		int dimensionNumber = 0;
		int length = 0;
		int width = 0;
		int height = 0;

		string currentDimension = "";
		
		//Loops through the line and stores the length, width and height.
		for (int i = 0; i < line.size(); i++)
		{
			if (i == line.size() - 1)
			{
				currentDimension += line[i];
			}

			if (line[i] != 'x' && i != line.size() - 1)
			{
				currentDimension += line[i];
			}

			else
			{
				switch (dimensionNumber)
				{
					case 0:
						length = stoi(currentDimension);
						break;
						
					case 1:
						width = stoi(currentDimension);
						break;

					case 2:
						height = stoi(currentDimension);
						break;
				}

				dimensionNumber++;
				currentDimension = "";
			}
		}

		//Get the area of each side.
		int firstTotal = length * width;
		int secondTotal = width * height;
		int thirdTotal = height * length;
		int smallestArea = 0;

		//Find the smallest area.
		if (firstTotal <= secondTotal && firstTotal <= thirdTotal)
		{
			smallestArea = firstTotal;
		}

		if (secondTotal <= firstTotal && secondTotal <= thirdTotal)
		{
			smallestArea = secondTotal;
		}

		if (thirdTotal <= firstTotal && thirdTotal <= secondTotal)
		{
			smallestArea = thirdTotal;
		}
		
		//Add the feet of wrapping paper needs for this present to the total feet.
		totalFeet += (2 * firstTotal) + (2 * secondTotal) + (2 * thirdTotal) + smallestArea;

		//Get the perimeter of each side.
		int perimeterOne = (length * 2) + (width * 2);
		int perimeterTwo = (length * 2) + (height * 2);
		int perimeterThree = (height * 2) + (width * 2);
		int smallestPerimeter = 0;

		//Find the smallest perimeter.
		if (perimeterOne <= perimeterTwo && perimeterOne <= perimeterThree)
		{
			smallestPerimeter = perimeterOne;
		}

		if (perimeterTwo <= perimeterOne && perimeterTwo <= perimeterThree)
		{
			smallestPerimeter = perimeterTwo;
		}

		if (perimeterThree <= perimeterOne && perimeterThree <= perimeterTwo)
		{
			smallestPerimeter = perimeterThree;
		}

		//Get the Cubic Feet of volume the present.
		int cubicFeet = length * width * height;

		//Add the total feet of ribbon needed for this present to the total ribbon feet.
		totalRibbonFeet += smallestPerimeter + cubicFeet;
	}

	cout << to_string(totalRibbonFeet) + " feet of ribbon is needed for these presents." << endl;

	dimensionsFile.close();
	return totalFeet;
}