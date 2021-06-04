#include <iostream>
#include <string>

#include "DayOne.h"
#include "DayTwo.h"
#include "DayThree.h"
#include "DayFive.h"
#include "DaySeven.h"

using namespace std;

int main()
{
    //Day One Answers
    cout << "The resulting frequency is: " + to_string(GetFinalFrequency()) << endl;

    //Day Two Answers
    cout << "The box checksum is: " + to_string(GetBoxChecksum()) << endl;
    cout << "The common letters of the two correct Box ID's are: " + GetCommonLetters() << endl;

    //Day Three Answers
    cout << "The square inches of conflicting claims is: " + to_string(GetSquareInches(1)) << endl;
    cout << "The claim ID that does not conflict with any other claims is: " + to_string(GetSquareInches(2)) << endl;

    //Day Five Answers
    ReadPolymer();
    cout << "The amount of units remaining after the polymer has finished reacting is: " + to_string(ReactPolymer(polymer)) << endl;
    cout << "The amount of units remaining after the problem unit has been removed and the polymer has finished reacting is: " + to_string(FindProblemUnit()) << endl;

    //Day Seven Answers
    ReadSteps();
    cout << "The order of the steps is: " + DetermineOrder();
}
