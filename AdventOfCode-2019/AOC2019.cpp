#include "DayOne.h"
#include "DayTwo.h"
#include "DayFour.h"
#include "DayEight.h"

int main()
{
    //Day One Answers
    cout << "The total fuel requirement following the first method is: " + to_string(GetFuelRequirements(1)) << endl;
    cout << "The total fuel requirement following the second method is: " + to_string(GetFuelRequirements(2)) << endl;

    //Day Two Answers
    ReadProgram();
    cout << "The value left at position 0 is: " + to_string(RunGravityProgram(1)) << endl;
    cout << "The noun and verb combination that produces 19690720 is: " + to_string(RunGravityProgram(2)) << endl;

    //Day Four Answers
    cout << "The number of valid passwords within the given range is: " + to_string(GetValidPasswords(178416, 676461, 0)) << endl;
    cout << "The number of valid passwords within the given range is: " + to_string(GetValidPasswords(178416, 676461, 1)) << endl;

    //Day Eight Answers
    cout << "The number of 1 digits multiplied by the number of 2 digits of the correct layer is: " + to_string(CheckCorruption()) << endl;
    DecodeImage();
}