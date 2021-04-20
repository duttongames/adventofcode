#include <iostream>

#include "DayOne.h"
#include "DayTwo.h"
#include "DayFour.h"
#include "DayFive.h"
#include "DaySix.h"

int main()
{
    //Day One Answers
    cout << "The Captcha Solution using the first method is: " + to_string(SolveCaptcha(1)) << endl;
    cout << "The Captcha Solution using the second method is: " + to_string(SolveCaptcha(2)) << endl;

    //Day Two Answers
    cout << "The checksum for the spreadsheet is: " + to_string(GetChecksum()) << endl;
    cout << "The sum of each row's result is: " + to_string(GetDivisibleValues()) << endl;

    //Day Three Answers

    //Day Four Answers
    cout << "The amount of valid passphrases following the first system policy is: " + to_string(GetValidPassphrases(1)) << endl;
    cout << "The amount of valid passphrases following the second system policy is: " + to_string(GetValidPassphrases(2)) << endl;

    //Day Five Answers
    cout << "The amount of steps taken to reach the exit for the first offset change method is: " + to_string(FindExit(1)) << endl;
    cout << "The amount of steps taken to reach the exit for the second offset change method is: " + to_string(FindExit(2)) << endl;

    //Day Six Answers
    cout << "The amount of cycles before a duplicate configuration is produced is: " + to_string(DetermineDupeConfig()) << endl;
}