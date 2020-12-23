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
void GetGameState()
{
	for (int i = 0; i < playerOneDeck.size(); i++)
	{
		cout << playerOneDeck[i] << endl;
	}

	cout << endl;

	for (int i = 0; i < playerTwoDeck.size(); i++)
	{
		cout << playerTwoDeck[i] << endl;
	}
}

//Gets the player's current score.
int GetPlayerScore(int playerID)
{
	int totalScore = 0;

	if (playerID == 1)
	{
		int scoreMultiplier = playerOneDeck.size();

		for (int i = 0; i < playerOneDeck.size(); i++)
		{
			totalScore += playerOneDeck[i] * scoreMultiplier;
			scoreMultiplier--;
		}
	}

	else
	{
		int scoreMultiplier = playerTwoDeck.size();

		for (int i = 0; i < playerTwoDeck.size(); i++)
		{
			totalScore += playerTwoDeck[i] * scoreMultiplier;
			scoreMultiplier--;
		}
	}

	return totalScore;
}

//Plays a game of combat until one player wins.
void PlayGame()
{
	GetDecks();

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
		cout << "Player One has won with a score of: " + to_string(GetPlayerScore(1));
	}

	else
	{
		cout << "Player Two has won with a score of: " + to_string(GetPlayerScore(2));
	}
}