#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Reads the homework equations and solves them according to the unique rules.
long long SolveHomework()
{
	string line;

	ifstream equations("Homework.txt");

	long long finalTotal = 0;

	int lineCounter = 1;

	//Get the input from the txt file.
	while (getline(equations, line))
	{
		long long equationTotal = 0;
		int offset = 0;
		int numbers = 0;
		bool doublePar = false;
		vector<char> currentOperators;
		vector<long long> currentNumbers;

		for (int i = 0; i < line.size() + 1; i++)
		{
			if (currentOperators.size() > 0 + offset && currentNumbers.size() > 1 + offset)
			{
				long long total = 0;

				//Perform the current operation and add it to the current total.
				if (currentOperators[0 + offset] == '+')
				{
					total += currentNumbers[0 + offset] + currentNumbers[1 + offset];
				}

				if (currentOperators[0 + offset] == '-')
				{
					total += currentNumbers[0 + offset] - currentNumbers[1 + offset];
				}

				if (currentOperators[0 + offset] == '*')
				{
					total += currentNumbers[0 + offset] * currentNumbers[1 + offset];
				}

				cout << to_string(currentNumbers[0 + offset]) + " " + currentOperators[0 + offset] + " " + to_string(currentNumbers[1 + offset]) + " = " + to_string(total) << endl;

				currentOperators.erase(currentOperators.begin() + offset, currentOperators.end());
				currentNumbers.erase(currentNumbers.begin() + offset, currentNumbers.end());

				if (offset > 0)
				{
					equationTotal += total;
				}

				else
				{
					equationTotal = total;
				}

				currentNumbers.push_back(total);
			}

			if (i < line.size())
			{
				//If the character is a number, push it to the numbers list.
				if (isdigit(line[i]))
				{
					int digit = line[i] - '0';
					currentNumbers.push_back(digit);
					numbers++;
				}

				//If the character is an operator, push it to the operators list.
				else if (line[i] == '+' || line[i] == '*' || line[i] == '-')
				{
					currentOperators.push_back(line[i]);
				}
				
				//If the character is a parentheses, increase the offset.
				else if (line[i] == '(')
				{
					int tempNumbers = 0;

					if (line[0] == '(' && line[1] != '(')
					{
						tempNumbers = 1;
					}

					if (i < line.size() - 1 && line[i + 1] == '(' && i != 0)
					{
						offset++;
						numbers = 0;
						doublePar = true;
					}

					else if (numbers > tempNumbers)
					{
						offset++;
						numbers = 0;
					}

					else if (i == 0 && line[i + 1] != '(' && ! isdigit(line[i + 1]))
					{
						offset++;
						numbers = 0;
					}

					else if (i != 0 && i != 1 && line[i + 1] != '(' && isdigit(line[i + 1]) && doublePar == false)
					{
						offset++;
						numbers = 0;
					}
				}

				else if (line[i] == ')')
				{
					if (doublePar)
					{
						doublePar = false;
					}

					else if (offset - 1 > -1)
					{
						offset--;
					}
				}
			}
		}

		lineCounter++;
		finalTotal += equationTotal;
	}

	return finalTotal;
}