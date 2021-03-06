#include "DayOne.h"
#include "DayTwo.h"
#include "DayThree.h"
#include "DayFour.h"
#include "DayFive.h"
#include "DaySix.h"
#include "DaySeven.h"
#include "DayEight.h"
#include "DayNine.h"
#include "DayTen.h"
#include "DayEleven.h"
#include "DayTwelve.h"
#include "DayThirteen.h"
#include "DayFourteen.h"
#include "DayFifteen.h"
#include "DaySixteen.h"
#include "DaySeventeen.h"
#include "DayEighteen.h"
#include "DayNineteen.h"
#include "DayTwentyTwo.h"
#include "DayTwentyThree.h"

int main()
{
	//cout << ExpenseFix() << endl;
	//cout << ExpenseFixTriple() << endl;
	//cout << "Valid Passwords: " + to_string(CheckPasswords(1)) << endl;
	//cout << "Valid Passwords: " + to_string(CheckPasswords(2)) << endl;

	long long treesOne = CountTrees(1, 1);
	long long treesTwo = CountTrees(3, 1);
	long long treesThree = CountTrees(5, 1);
	long long treesFour = CountTrees(7, 1);
	long long treesFive = CountTrees(1, 2);

	//cout << "Trees Encountered: " + to_string(treesOne) << endl;
	//cout << "Trees Encountered: " + to_string(treesTwo) << endl;
	//cout << "Trees Encountered: " + to_string(treesThree) << endl;
	//cout << "Trees Encountered: " + to_string(treesFour) << endl;
	//cout << "Trees Encountered: " + to_string(treesFive) << endl;

	long long test = treesOne * treesTwo * treesThree * treesFour * treesFive;
	//cout << "Trees Multiplied: " + to_string(test) << endl;

	//cout << "Valid Passports: " + to_string(CheckPassports()) << endl;

	//cout << "My Seat ID is: " + to_string(GetHighestID()) << endl;

	//cout << "Questions answered yes: " + to_string(CountAnswers()) << endl;

	//cout << "The amount of bag colours that contain a shiny gold bag is: " + to_string(FindBagsThatContain("shiny gold")) << endl;

	int bags = 0;
	//cout << "A shiny gold bag contains: " + to_string(CountBags("shiny gold", bags, 1)) + " bags" << endl;

	//cout << "The Accumulator value once the program has terminated is: " + to_string(GetAccValue()) << endl;

	//cout << "The encryption weakness is: " + to_string(GetEncryptionWeakness(GetInvalidNumber())) << endl;

	//cout << "The Three Jolt Differences Multiplied by the One Jolt Differences is: " + to_string(GetJoltDifferences()) << endl;

	//cout << "The Total Number of Adapter Combinations is: " + to_string(GetTotalCombinations()) << endl;

	//ReadSeats();

	//cout << "The Total Number of Occupied Seats based on the first set of rules is: " + to_string(GetOccupiedSeats()) << endl;

	//ReadSeats();

	//cout << "The Total Number of Occupied Seats based on the second set of rules is: " + to_string(GetOccupiedSeatsTwo()) << endl;

	//ReadCommands();

	//cout << "The Manhattan Distance from the ship's starting position is: " + to_string(GetManhattanDistance()) << endl;

	//cout << "The Manhattan Distance from the ship's starting position following the second method is: " + to_string(GetManhattanDistanceTwo()) << endl;

	//ReadBusNotes(0);

	//cout << "The earliest bus ID multiplied by the number of minutes to wait is: " + to_string(GetEarliestBus()) << endl;

	//ReadBusNotes(1);

	//cout << "The earliest timestamp where all buses depart subsequently after each other is: " + to_string(GetEarliestDeparture()) << endl;

	//ReadInitProgram();

	//cout << "The 2020th number is: " +  to_string(GetLastNumber(2020)) << endl;
	//cout << "The 30000000th number is: " + to_string(GetLastNumber(30000000)) << endl;

	//cout << "The ticket error rate is: " + to_string(GetErrorRate()) << endl;
	//cout << "The departure score is: " + to_string(GetDepartureValues()) << endl;

	//GetDepartureValues();

	//cout << "The amount of active cubes after six cycles is: " + to_string(Cycle());

	//cout << "The total sum of the equations is: " + to_string(SolveHomework()) << endl;

	ReadRulesAndMessages();

	vector<string> empty;
	vector<string> debugMessages = GetValidMessages("0", empty, 0);

	for (int i = 0; i < debugMessages.size(); i++)
	{
		cout << debugMessages[i] << endl;
	}

	for (int i = 0; i < rules["1"].size(); i++)
	{
		for (int j = 0; j < rules["1"][i].size(); j++)
		{
			cout << rules["1"][i][j] + ", ";
		}

		cout << endl;
	}

	//GetDecks();
	//PlayCombat();
	//PlayRecursiveCombat(playerOneDeck, playerTwoDeck, 0);

	//cout << "The final formation of the cup labels is: " + SimulateMoves(100) << endl;

	return 0;
}