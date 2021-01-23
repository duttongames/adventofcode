#include <iostream>

#include "DayOne.h"
#include "DayTwo.h"
#include "DayThree.h"
#include "DayFour.h"
#include "DayFive.h"
#include "DaySix.h"

using namespace std;

int main()
{
    //Day One Answers
    cout << "Easter Bunny HQ is " + to_string(GetBlockDistance()) + " blocks away." << endl;

    //Day Two Answers
    cout << "The Bathroom Code for the first keypad is: " + GetBathroomCode(firstKeypad) << endl;
    cout << "The Bathroom Code for the second keypad is: " + GetBathroomCode(secondKeypad) << endl;

    //Day Three Answers
    cout << "The amount of possible triangles for Part 1 is: " + to_string(GetPossibleTriangles(1)) << endl;
    cout << "The amount of possible triangles for Part 2 is: " + to_string(GetPossibleTriangles(2)) << endl;

    //Day Four Answers
    cout << "The sum of all the valid sector ID's is: " + to_string(GetValidRooms()) << endl;
    cout << "The sector ID of the North Pole Object Storage room is: " + to_string(DecryptRooms("northpole object storage")) << endl;

    //Day Five Answers
    //cout << "The Password for the first door is: " + GetDoorPassword(1) << endl;
    //cout << "The Password for the second door is: " + GetDoorPassword(2) << endl;

    //Day Six Answers
    cout << "The error corrected message using the first method is: " + ErrorCorrectMessage(1) << endl;
    cout << "The error corrected message using the second method is: " + ErrorCorrectMessage(2) << endl;
}
