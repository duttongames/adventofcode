// AOC2015.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "DayOne.h";
#include "DayTwo.h";
#include "DayThree.h";
#include "DayFour.h"
#include "DayFive.h";
#include "DaySix.h";
#include "DaySeven.h";
#include "DayEight.h";
#include "DayNine.h";
#include "DayTen.h"
#include "DayEleven.h"
#include "DayTwelve.h";
#include "DayFourteen.h";

int main()
{
    //Day One Answers
    cout << "The instructions take Santa to Floor " + to_string(ReadFloors(0)) << endl;

    //Day Two Answers
    cout << "The amount of wrapping paper needed in feet is: " + to_string(GetFeetNeeded()) << endl;

    //Day Three Answers
    cout << "The total amount of houses delivered to is: " + to_string(GetDeliveredHouses()) << endl;

    //Day Four Answers
    //cout << "The lowest possible number for a MD5 hash that starts with six zeroes is: " + to_string(FindSuitableHash(2)) << endl;

    //Day Five Answers
    cout << "The amount of nice strings in the list is: " + to_string(GetNiceStrings(1)) << endl;
    cout << "The amount of nice strings in the list is: " + to_string(GetNiceStrings(2)) << endl;

    //Day Six Answers
    cout << "The amount of lights that are lit is: " + to_string(GetLitLights(1)) << endl;
    cout << "The amount of lights that are lit is: " + to_string(GetLitLights(2)) << endl;

    //Day Seven Answers
    cout << "The signal provided to wire 'a' is: " + to_string(AssembleCircuit()) << endl;

    //Day Eight Answers
    cout << "The number of string literal characters minus the number of characters in memory is: " + to_string(GetNumberOfCharacters()) << endl;

    //Day Nine Answers
    cout << "The distance of the shortest route is: " + to_string(GetShortestDistance()) << endl;

    //Day Ten Answers
    cout << "The length of the Look and Say result after 40 iterations is: " + to_string(LookAndSay("1321131112", 40).size()) << endl;
    cout << "The length of the Look and Say result after 50 iterations is: " + to_string(LookAndSay("1321131112", 50).size()) << endl;

    //Day Eleven Answers
    string firstPassword = GetNextPassword("vzbxkghb");
    cout << "Santa's next password is: " + firstPassword << endl;
    cout << "Santa's next password after the first is: " + GetNextPassword(firstPassword) << endl;

    //Day Twelve Answers
    cout << "The total of all the numbers in the document is: " + to_string(CountNumbers()) << endl;

    //Day Fourteen Answers
    cout << "The distance the fastest reindeer has travelled after 2503 seconds is: " + to_string(GetFastestReindeer(0)) << endl;
    cout << "The winning reindeer has the following points: " + to_string(GetFastestReindeer(1)) << endl;
}