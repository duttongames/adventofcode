#include <iostream>
#include <string>

#include "DayOne.h"
#include "DayTwo.h"

using namespace std;

int main()
{
    //Day One Answers.
    cout << "The resulting frequency is: " + to_string(GetFinalFrequency()) << endl;

    //Day Two Answers.
    cout << "The box checksum is: " + to_string(GetBoxChecksum()) << endl;
    cout << "The common letters of the two correct Box ID's are: " + GetCommonLetters() << endl;
}
