#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

static int ExpenseFix()
{
	vector<int> reportNumbers;
	string line;

	ifstream report("ExpenseReport.txt");

	while (getline(report, line))
	{
		reportNumbers.push_back(stoi(line));
	}

	for (int i = 0; i < reportNumbers.size() - 1; i++)
	{
		for (int j = 1; j < reportNumbers.size(); j++)
		{
			if (reportNumbers[i] + reportNumbers[j] == 2020)
			{
				cout << reportNumbers[i] << endl;
				cout << reportNumbers[j] << endl;

				return reportNumbers[i] * reportNumbers[j];
			}
		}
	}
}

static int ExpenseFixTriple()
{
	vector<int> reportNumbers;
	string line;

	ifstream report("ExpenseReport.txt");

	while (getline(report, line))
	{
		reportNumbers.push_back(stoi(line));
	}

	for (int i = 0; i < reportNumbers.size() - 1; i++)
	{
		for (int j = 1; j < reportNumbers.size(); j++)
		{
			for (int k = 1; k < reportNumbers.size(); k++)
			{
				if (reportNumbers[i] + reportNumbers[j] + reportNumbers[k] == 2020)
				{
					cout << reportNumbers[i] << endl;
					cout << reportNumbers[j] << endl;
					cout << reportNumbers[k] << endl;

					return reportNumbers[i] * reportNumbers[j] * reportNumbers[k];
				}
			}
		}
	}
}