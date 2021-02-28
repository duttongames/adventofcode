#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>

//Takes two words as an input and returns whether they are an anagram of each other or not.
bool IsAnagram(string wordOne, string wordTwo)
{
	//If the words are not the same size, they are not an anagram.
	if (wordOne.size() != wordTwo.size())
	{
		return false;
	}

	//Loop through the words and count the occurences of each letter.
	map<char, int> firstWordLetters;
	map<char, int> secondWordLetters;

	for (int i = 0; i < wordOne.size(); ++i)
	{
		firstWordLetters[wordOne[i]]++;
		secondWordLetters[wordTwo[i]]++;
	}

	//Determine if the words are an anagram by checking if the letter maps are equal.
	if (!equal(firstWordLetters.begin(), firstWordLetters.end(), secondWordLetters.begin()))
	{
		return false;
	}

	return true;
}

//Determines the number of passphrases that are valid.
int GetValidPassphrases(int systemPolicy)
{
	int validPassphrases = 0;

	string line;

	ifstream passphrases("Passphrases.txt");

	//Loop through each Passphrase.
	while (getline(passphrases, line))
	{
		map<string, int> words;
		string currentWord = "";
		bool duplicate = false;

		currentWord += line[0];
		
		//Loop through each character on the line.
		for (int i = 1; i < line.size(); ++i)
		{
			//Parse the next word.
			if (line[i] != ' ')
			{
				currentWord += line[i];
			}

			//Push the parsed word to the map and add to its counter.
			if (line[i] == ' ' || i == line.size() - 1)
			{
				words[currentWord]++;

				//The word is a duplicate so break the loop and move onto the next line instead of wasting time.
				if (words[currentWord] > 1)
				{
					duplicate = true;
					break;
				}

				//If using the second system policy, check if the word is an anagram of any other words in the passphrase.
				if (systemPolicy == 2)
				{
					map<string, int>::iterator wordIterator;

					for (wordIterator = words.begin(); wordIterator != words.end(); wordIterator++)
					{
						//If the word is not the same and is an anagram, break the loop.
						if (wordIterator->first != currentWord)
						{
							if (IsAnagram(currentWord, wordIterator->first))
							{
								duplicate = true;
								i = line.size();
								break;
							}
						}
					}
				}

				currentWord = "";
			}
		}

		//Increment the number of valid passphrases if the current passphrase is valid.
		if (!duplicate)
		{
			validPassphrases++;
		}
	}

	return validPassphrases;
}