#include <iostream>

#include "DayOne.h"
#include "DayTwo.h"

int main()
{
    //Day One Answers
    cout << "The Captcha Solution using the first method is: " + to_string(SolveCaptcha(1)) << endl;
    cout << "The Captcha Solution using the second method is: " + to_string(SolveCaptcha(2)) << endl;

    //Day Two Answers
    cout << "The checksum for the spreadsheet is: " + to_string(GetChecksum()) << endl;
    cout << "The sum of each row's result is: " + to_string(GetDivisibleValues()) << endl;
}