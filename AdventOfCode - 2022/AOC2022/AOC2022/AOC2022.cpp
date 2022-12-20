#include "DayOne.h"

int main()
{
    LoadCalories();
    cout << "Total number of calories being carried by the elf with the most calories is: " << GetMostCalories() << endl;
    cout << "Total number of calories being carried by the three elves with the most calories is: " << GetTopThreeCalories() << endl;
}
