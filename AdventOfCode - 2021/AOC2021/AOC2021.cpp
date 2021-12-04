#include <iostream>
#include "DayOne.h"
#include "DayTwo.h"

int main()
{
    cout << "The number of larger measurements is: " << GetLargerMeasurements() << endl;
    cout << "The number of larger measurement sums is: " << GetLargerMeasurementsSum() << endl;
    cout << "The final horizontal position multiplied by the final depth is: " << CalculatePosition() << endl;
    cout << "The final horizontal position multiplied by the final depth is: " << CalculatePositionAim() << endl;
}
