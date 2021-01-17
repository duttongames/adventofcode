// AOC2015.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "DayOne.h";
#include "DayTwo.h";
#include "DayThree.h";
#include "DayFive.h";

int main()
{
    //Day One Answers
    cout << "The instructions take Santa to Floor " + to_string(ReadFloors(0)) << endl;

    //Day Two Answers
    cout << "The amount of wrapping paper needed in feet is: " + to_string(GetFeetNeeded()) << endl;

    //Day Three Answers
    cout << "The total amount of houses delivered to is: " + to_string(GetDeliveredHouses()) << endl;

    //Day Five Answers
    cout << "The amount of nice strings in the list is: " + to_string(GetNiceStrings(1)) << endl;
    cout << "The amount of nice strings in the list is: " + to_string(GetNiceStrings(2)) << endl;
}