#include "DayOne.h"
#include "DayTwo.h"
#include "DayThree.h"
#include "DayFour.h"

int main()
{
	cout << ExpenseFix() << endl;
	cout << ExpenseFixTriple() << endl;
	cout << "Valid Passwords: " + to_string(CheckPasswords(1)) << endl;
	cout << "Valid Passwords: " + to_string(CheckPasswords(2)) << endl;

	long long treesOne = CountTrees(1, 1);
	long long treesTwo = CountTrees(3, 1);
	long long treesThree = CountTrees(5, 1);
	long long treesFour = CountTrees(7, 1);
	long long treesFive = CountTrees(1, 2);

	cout << "Trees Encountered: " + to_string(treesOne) << endl;
	cout << "Trees Encountered: " + to_string(treesTwo) << endl;
	cout << "Trees Encountered: " + to_string(treesThree) << endl;
	cout << "Trees Encountered: " + to_string(treesFour) << endl;
	cout << "Trees Encountered: " + to_string(treesFive) << endl;

	long long test = treesOne * treesTwo * treesThree * treesFour * treesFive;
	cout << "Trees Multiplied: " + to_string(test) << endl;

	cout << "Valid Passports: " + to_string(CheckPassports()) << endl;

	return 0;
}