#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

vector<int> playerOneDeck;
vector<int> playerTwoDeck;

//Get both player's starting decks.
void GetDecks()
{
	string line;
	int playerNumber = 1;

	ifstream cards("Cards.txt");

	//Get the input from the txt file.
	while (getline(cards, line))
	{
		if (line == "")
		{
			playerNumber++;
		}

		else if (playerNumber == 1)
		{
			playerOneDeck.push_back(stoi(line));
		}

		else
		{
			playerTwoDeck.push_back(stoi(line));
		}
	}
}

//Gets the state of the game by printing both player one and player two's decks. For Debugging.
void GetGameState(vector<int> firstDeck, vector<int> secondDeck)
{
	for (int i = 0; i < firstDeck.size(); i++)
	{
		cout << firstDeck[i] << endl;
	}

	cout << endl;

	for (int i = 0; i < secondDeck.size(); i++)
	{
		cout << secondDeck[i] << endl;
	}

	cout << endl;
}

//Gets the player's current score.
int GetPlayerScore(int playerID, vector<int> firstDeck, vector<int> secondDeck)
{
	int totalScore = 0;

	if (playerID == 1)
	{
		int scoreMultiplier = firstDeck.size();

		for (int i = 0; i < firstDeck.size(); i++)
		{
			totalScore += firstDeck[i] * scoreMultiplier;
			scoreMultiplier--;
		}
	}

	else
	{
		int scoreMultiplier = secondDeck.size();

		for (int i = 0; i < secondDeck.size(); i++)
		{
			totalScore += secondDeck[i] * scoreMultiplier;
			scoreMultiplier--;
		}
	}

	return totalScore;
}

//Plays a game of combat until one player wins.
void PlayCombat()
{
	//Loop until a player has no cards.
	while (playerOneDeck.size() > 0 && playerTwoDeck.size() > 0)
	{
		//Erase and save the cards used in this round.
		int playerOneCard = playerOneDeck[0];
		playerOneDeck.erase(playerOneDeck.begin());

		int playerTwoCard = playerTwoDeck[0];
		playerTwoDeck.erase(playerTwoDeck.begin());

		//The player with the higher valued card wins the round and gets the two cards added to the bottom of their deck.
		if (playerOneCard > playerTwoCard)
		{
			playerOneDeck.push_back(playerOneCard);
			playerOneDeck.push_back(playerTwoCard);
		}

		else
		{
			playerTwoDeck.push_back(playerTwoCard);
			playerTwoDeck.push_back(playerOneCard);
		}
	}

	if (playerOneDeck.size() > 0)
	{
		cout << "Player One has won with a score of: " + to_string(GetPlayerScore(1, playerOneDeck, playerTwoDeck));
	}

	else
	{
		cout << "Player Two has won with a score of: " + to_string(GetPlayerScore(2, playerOneDeck, playerTwoDeck));
	}
}


//Plays a game of recursive combat until one player wins.
int PlayRecursiveCombat(vector<int> firstDeck, vector<int> secondDeck, int recursiveDepth)
{
	int roundNumber = 0;

	//Used to store round layouts for Recursive combat.
	vector<vector<int>> playerOneRoundLayouts;
	vector<vector<int>> playerTwoRoundLayouts;

	vector<int> deckOne;
	vector<int> deckTwo;

	for (int i = 0; i < firstDeck.size(); i++)
	{
		deckOne.push_back(firstDeck[i]);
	}

	for (int i = 0; i < secondDeck.size(); i++)
	{
		deckTwo.push_back(secondDeck[i]);
	}

	while (deckOne.size() > 0 && deckTwo.size() > 0)
	{
		roundNumber++;
		
		//cout << roundNumber << endl;

		//Check the current deck layout for both players is not the same as any previous rounds.
		bool sameLayout = false;

		for (int i = 0; i < playerOneRoundLayouts.size(); i++)
		{
			if (playerOneRoundLayouts[i].size() == deckOne.size() && playerTwoRoundLayouts[i].size() == deckTwo.size())
			{
				int sameCards = 0;

				for (int j = 0; j < playerOneRoundLayouts[i].size(); j++)
				{
					if (playerOneRoundLayouts[i][j] == deckOne[j])
					{
						sameCards++;
					}
				}

				if (sameCards == playerOneRoundLayouts[i].size())
				{
					int sameCardsTwo = 0;

					for (int j = 0; j < playerTwoRoundLayouts[i].size(); j++)
					{
						if (playerTwoRoundLayouts[i][j] == deckTwo[j])
						{
							sameCardsTwo++;
						}
					}

					if (sameCardsTwo == playerTwoRoundLayouts[i].size())
					{
						sameLayout = true;
						break;
					}
				}
			}
		}

		//Give Player 1 the win as the layout is the same as a previous round.
		if (sameLayout)
		{
			if (recursiveDepth == 0)
			{
				cout << "Player One has won the game with a score of: " + to_string(GetPlayerScore(1, deckOne, deckTwo)) << endl;
			}

			return 1;
		}

		else
		{
			//GetGameState(deckOne, deckTwo);

			//Save each player's deck layout so it can be checked against later.
			playerOneRoundLayouts.push_back(deckOne);
			playerTwoRoundLayouts.push_back(deckTwo);

			//Erase and save the cards used in this round.
			int playerOneCard = deckOne[0];
			deckOne.erase(deckOne.begin());

			int playerTwoCard = deckTwo[0];
			deckTwo.erase(deckTwo.begin());

			//Start another game if both player's have a card value greater than or equal to their deck size.
			if (deckOne.size() >= playerOneCard && deckTwo.size() >= playerTwoCard)
			{
				vector<int> deckOneCopy;
				vector<int> deckTwoCopy;

				for (int i = 0; i < playerOneCard; i++)
				{
					deckOneCopy.push_back(deckOne[i]);
				}

				for (int i = 0; i < playerTwoCard; i++)
				{
					deckTwoCopy.push_back(deckTwo[i]);
				}

				int subRoundWinner = PlayRecursiveCombat(deckOneCopy, deckTwoCopy, recursiveDepth + 1);

				if (subRoundWinner == 1)
				{
					deckOne.push_back(playerOneCard);
					deckOne.push_back(playerTwoCard);
				}

				else if (subRoundWinner == 2)
				{
					deckTwo.push_back(playerTwoCard);
					deckTwo.push_back(playerOneCard);
				}
			}

			//The player with the higher valued card wins the round and gets the two cards added to the bottom of their deck.
			else if (playerOneCard > playerTwoCard)
			{
				deckOne.push_back(playerOneCard);
				deckOne.push_back(playerTwoCard);
			}

			else
			{
				deckTwo.push_back(playerTwoCard);
				deckTwo.push_back(playerOneCard);
			}
		}
	}

	if (deckOne.size() > 0)
	{
		if (recursiveDepth == 0)
		{
			cout << "Player One has won the game with a score of: " + to_string(GetPlayerScore(1, deckOne, deckTwo)) << endl;
		}

		return 1;
	}

	else if (deckTwo.size() > 0)
	{
		if (recursiveDepth == 0)
		{
			cout << "Player Two has won the game with a score of: " + to_string(GetPlayerScore(2, deckOne, deckTwo)) << endl;
		}

		return 2;
	}

	return 0;
}