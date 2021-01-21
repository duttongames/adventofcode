#include <iostream>


#include "DayOne.h"
#include "DayTwo.h"

using namespace std;

int main()
{
    //Day One Answers
    cout << "Easter Bunny HQ is " + to_string(GetBlockDistance()) + " blocks away." << endl;

    //Day Two Answers
    cout << "The Bathroom Code for the first keypad is: " + GetBathroomCode(firstKeypad) << endl;
    cout << "The Bathroom Code for the second keypad is: " + GetBathroomCode(secondKeypad) << endl;
}
