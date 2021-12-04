#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Intcode.h"

using namespace std;

//Run the series of diagnostic tests and output a diagnostic code after passing all of them.
void RunTests()
{
	//Go through all the diagnostic tests.
	ifstream testFile("DiagnosticTests.txt");
	string line;

	//The current Mode. 0 = Parameter Mode, 1 = Position Mode
	int currentMode = 0;
	
	while (getline(testFile, line))
	{


		for (int i = 0; i < line.size(); ++i)
		{

		}
	}
}