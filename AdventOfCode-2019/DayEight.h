#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

map<int, vector<char>> imageLayers;

//Check the image for corruption by finding the layer with the fewest digits and mulitply
//the number of 1 digits by the number of 2 digits in that layer.
int CheckCorruption()
{
	ifstream imageFile;
	imageFile.open("ImageData.txt");
	string line;

	vector<int> zeroDigits;
	vector<int> oneDigits;
	vector<int> twoDigits;

	zeroDigits.push_back(0);
	oneDigits.push_back(0);
	twoDigits.push_back(0);

	char currentChar;

	int characterCounter = 0;
	int imageSize = 150;

	int currentLayer = 0;

	vector<char> layerData;

	//Loop through the image data.
	while (imageFile.get(currentChar))
	{
		//Detect when reaching the end of the image file.
		if (imageFile.peek(), imageFile.eof())
		{
			break;
		}

		characterCounter++;

		//Read the current image layer.
		switch (currentChar)
		{
		case '0':
			zeroDigits[currentLayer]++;
			break;

		case '1':
			oneDigits[currentLayer]++;
			break;

		case '2':
			twoDigits[currentLayer]++;
			break;
		}

		layerData.push_back(currentChar);
		
		//Move onto the next image layer.
		if (characterCounter >= imageSize)
		{
			zeroDigits.push_back(0);
			oneDigits.push_back(0);
			twoDigits.push_back(0);
			imageLayers[currentLayer] = layerData;
			layerData.clear();
			currentLayer++;
			characterCounter = 0;
		}
	}

	imageFile.close();

	//Find the layer with the least 0 digits.
	int lowestZeroDigits = zeroDigits[0];
	int lowestZeroIndex = 0;

	for (int i = 1; i < zeroDigits.size(); ++i)
	{
		if (zeroDigits[i] < lowestZeroDigits)
		{
			lowestZeroDigits = zeroDigits[i];
			lowestZeroIndex = i;
		}
	}

	//Return the number of 1 digits multiplied by the number of 2 digits. 
	return oneDigits[lowestZeroIndex] * twoDigits[lowestZeroIndex]; 
}

//Decode the image and display it in the console.
void DecodeImage()
{
	int columnCounter = 0;

	//Loop through each image layer.
	for (int i = 0; i < imageLayers[0].size(); ++i)
	{
		map<int, vector<char>>::iterator imageIterator;

		for (imageIterator = imageLayers.begin(); imageIterator != imageLayers.end(); ++imageIterator)
		{
			if (imageIterator->second[i] == '0')
			{
				cout << '.';
				break;
			}

			else if (imageIterator->second[i] == '1')
			{
				cout << '#';
				break;
			}
		}

		columnCounter++;

		if (columnCounter == 25)
		{			
			cout << endl;
			columnCounter = 0;
		}
	}
}