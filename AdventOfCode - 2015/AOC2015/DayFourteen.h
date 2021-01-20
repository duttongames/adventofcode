#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, vector<int>> reindeers; //Key is reindeer name, vector contains speed, flying time and resting time in that order.

//Outputs all the reindeers in the map. Used for debugging.
void ListReindeers()
{
	map<string, vector<int>>::iterator it;

	for (it = reindeers.begin(); it != reindeers.end(); it++)
	{
		cout << it->first + ": " + to_string(it->second[0]) + " speed, " + to_string(it->second[1]) + " flying time, " + to_string(it->second[2]) + " resting time." << endl;
	}
}

//Returns the distance the fastest reindeer has travelled after 2503 seconds or the highest amount of points accumulated after 2503 seconds based on the method.
int GetFastestReindeer(int method)
{
	ifstream reindeerFile("Reindeers.txt");
	string line;

	reindeers.clear();

	//Loop through each reindeer and add their data to the map.
	while (getline(reindeerFile, line))
	{
		string currentData = "";
		string currentReindeer = "";
		int dataNumber = 0;

		for (int i = 0; i < line.size(); i++)
		{
			//Parse only the data that is needed.
			if (line[i] != ' ')
			{
				if (dataNumber == 0 || isdigit(line[i]))
				{
					currentData += line[i];
				}
			}

			//Add the reindeer name as a key in the map.
			if (dataNumber == 0 && line[i] == ' ')
			{
				vector<int> emptyVector;
				reindeers[currentData] = emptyVector;
				currentReindeer = currentData;
				currentData = "";
				dataNumber++;
			}

			//Add the reindeer's speed, flying time and resting time to the map.
			else if (isdigit(line[i]) && !isdigit(line[i +1]))
			{
				reindeers[currentReindeer].push_back(stoi(currentData));
				currentData = "";
				dataNumber++;
			}
		}
	}

	reindeerFile.close();

	//Key is reindeer name, vector contains distance travelled, distance until changing state, current state and current score in that order. States: 1 = Flying, 0 = Resting.
	map<string, vector<int>> reindeerProgress;

	map<string, vector<int>>::iterator it;

	//Create a progress vector for each reindeer to track their progress.
	for (it = reindeers.begin(); it != reindeers.end(); it++)
	{
		vector<int> newProgressVector;
		newProgressVector.push_back(0);
		newProgressVector.push_back(it->second[1]);
		newProgressVector.push_back(1);
		newProgressVector.push_back(0);

		reindeerProgress[it->first] = newProgressVector;
	}

	//Simulate the race using a for loop with i representing seconds.
	for (int i = 1; i < 2504; i++)
	{
		int currentFurthestDistance = 0;

		for (it = reindeers.begin(); it != reindeers.end(); it++)
		{
			//Flying state.
			if (reindeerProgress[it->first][2] == 1)
			{
				reindeerProgress[it->first][0]+= reindeers[it->first][0];
			}

			//Reduce time until changing state.
			reindeerProgress[it->first][1]--;

			//Change State.
			if (reindeerProgress[it->first][1] <= 0)
			{
				//Change to Resting state.
				if (reindeerProgress[it->first][2] == 1)
				{
					reindeerProgress[it->first][2] = 0;
					reindeerProgress[it->first][1] = reindeers[it->first][2];
				}

				//Change to Flying state.
				else
				{
					reindeerProgress[it->first][2] = 1;
					reindeerProgress[it->first][1] = reindeers[it->first][1];
				}
			}

			//Determine which reindeer is in the lead.
			if (reindeerProgress[it->first][0] > currentFurthestDistance)
			{
				currentFurthestDistance = reindeerProgress[it->first][0];
			}
		}

		//Award a point to the reindeer in the lead, accounting for ties.
		for (it = reindeerProgress.begin(); it != reindeerProgress.end(); it++)
		{
			if (reindeerProgress[it->first][0] == currentFurthestDistance)
			{
				reindeerProgress[it->first][3]++;
			}
		}
	}

	int furthestDistance = 0;
	int mostPoints = 0;
	string fastestReindeer = "";

	for (it = reindeerProgress.begin(); it != reindeerProgress.end(); it++)
	{
		//Determine which reindeer travelled the furthest.
		if (method == 0)
		{
			if (furthestDistance < reindeerProgress[it->first][0])
			{
				furthestDistance = reindeerProgress[it->first][0];
				fastestReindeer = it->first;
			}
		}

		//Determine which reindeer has the most points.
		else
		{
			if (mostPoints < reindeerProgress[it->first][3])
			{
				mostPoints = reindeerProgress[it->first][3];
				fastestReindeer = it->first;
			}
		}
	}

	cout << "The winning reindeer is: " + fastestReindeer << endl;

	if (method == 0)
	{
		return furthestDistance;
	}

	else
	{
		return mostPoints;
	}

	return 0;
}