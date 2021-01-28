#include "DayOne.h"
#include "DayTwo.h"

int main()
{
    //Day One Answers
    cout << "The total fuel requirement following the first method is: " + to_string(GetFuelRequirements(1)) << endl;
    cout << "The total fuel requirement following the second method is: " + to_string(GetFuelRequirements(2)) << endl;

    //Day Two Answers
    ReadProgram();
    cout << "The value left at position 0 is: " + to_string(RunGravityProgram(1)) << endl;
    cout << "The noun and verb combination that produces 19690720 is: " + to_string(RunGravityProgram(2)) << endl;
}