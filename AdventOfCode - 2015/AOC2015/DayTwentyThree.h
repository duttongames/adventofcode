#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

unsigned int a;
unsigned int b;

int currentInstruction = 0;

vector<string> instructions;
vector<char> registers;
vector<int> offsets;

//Reads and saves the example program.
void ReadProgram()
{
	ifstream programFile("Program.txt");
	string line;

	//Loop through each instruction.
	while (getline(programFile, line))
	{
		//Determine the instruction, register and offset.
		string instruction = "";
		instruction += line[0];
		instruction += line[1];
		instruction += line[2];
		instructions.push_back(instruction);

		if (line[4] != 'a' && line[4] != 'b')
		{
			registers.push_back(' ');

			if (line[4] == '+')
			{
				offsets.push_back(stoi(line.substr(4, line.size())));
			}

			else
			{
				int offset = stoi(line.substr(4, line.size()));
				offsets.push_back(offset);
			}
		}

		else
		{
			registers.push_back(line[4]);

			if (line.size() > 5)
			{
				if (line[7] == '+')
				{
					offsets.push_back(stoi(line.substr(7, line.size())));
				}

				else
				{
					int offset = stoi(line.substr(7, line.size()));
					offsets.push_back(offset);
				}
			}

			else
			{
				offsets.push_back(0);
			}
		}
	}
}

//Executes the example program.
void ExecuteProgram()
{
	//Execute all the instructions until the program goes beyonds the bounds of the instructions.
	while (currentInstruction > -1 && currentInstruction < instructions.size())
	{
		//Perform the specified instruction.

		//Halfs the register's value.
		if (instructions[currentInstruction] == "hlf")
		{
			if (registers[currentInstruction] == 'a')
			{
				a /= 2;
			}

			else
			{
				b /= 2;
			}
		}

		//Triples the register's value.
		if (instructions[currentInstruction] == "tpl")
		{
			if (registers[currentInstruction] == 'a')
			{
				a *= 3;
			}

			else
			{
				b *= 3;
			}
		}

		//Increments the register's value.
		if (instructions[currentInstruction] == "inc")
		{
			if (registers[currentInstruction] == 'a')
			{
				a++;
			}

			else
			{
				b++;
			}
		}

		//Jumps by a specified offset to the next instruction.
		if (instructions[currentInstruction] == "jmp")
		{
			currentInstruction += offsets[currentInstruction];
		}

		//Jumps by a specified offset to the next instruction if the register is even.
		else if (instructions[currentInstruction] == "jie")
		{
			if (registers[currentInstruction] == 'a')
			{
				if (a % 2 == 0)
				{
					currentInstruction += offsets[currentInstruction];
				}

				else
				{
					currentInstruction++;
				}
			}

			else
			{
				if (b % 2 == 0)
				{
					currentInstruction += offsets[currentInstruction];
				}

				else
				{
					currentInstruction++;
				}
			}
		}

		//Jumps by a specified offset to the next instruction if the register is one.
		else if (instructions[currentInstruction] == "jio")
		{
			if (registers[currentInstruction] == 'a')
			{
				if (a == 1)
				{
					currentInstruction += offsets[currentInstruction];
				}

				else
				{
					currentInstruction++;
				}
			}

			else
			{
				if (b == 1)
				{
					currentInstruction += offsets[currentInstruction];
				}

				else
				{
					currentInstruction++;
				}
			}
		}

		else
		{
			currentInstruction++;
		}
	}
}