// AOC2015.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "DayOne.h";
#include "DayTwo.h";
#include "DayThree.h";

int main()
{
    cout << "The instructions take Santa to Floor " + to_string(ReadFloors(0)) << endl;

    cout << "The amount of wrapping paper needed in feet is: " + to_string(GetFeetNeeded()) << endl;

    cout << "The total amount of houses delivered to is: " + to_string(GetDeliveredHouses()) << endl;
}