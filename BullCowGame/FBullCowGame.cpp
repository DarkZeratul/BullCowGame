#pragma once

#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset();
}

FBullCowGame::~FBullCowGame()
{
}


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bMyGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,11},{6,14},{7,18} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

// Checks whether 
EGuessStatus FBullCowGame::IsValidGuess(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::NotOk_Length;
	}
	else if (!IsIsogram(Guess))
	{
		return EGuessStatus::NotOk_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::NotOk_UpperCase;
	}
	return EGuessStatus::Ok;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LettersSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LettersSeen[Letter])
		{ 
			return false; 
		}
		else
		{
			LettersSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() == 0) { return true; }

	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "ant"; // This MUST be an Isogram.

	MyCurrentTry = 1;	
	MyHiddenWord = HIDDEN_WORD;
	bMyGameIsWon = false;

	return;
}

// Counts the Number of Bulls & Cows and Increments Try # (Turn) by receiving a Valid Guess.
FBullCowCounter FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCounter BullCowCounter;

	// Compare the Letters of the Player's Guess against the Letters of the Hidden Word.
	int32 WordLength = MyHiddenWord.length(); // Assumes that the Hidden Word and Guess have the same Length.
	for (int32 i = 0; i < WordLength; i++)
	{
		if (Guess[i] == MyHiddenWord[i])
		{
			BullCowCounter.Bulls++;
		}
		else
		{
			for (int32 j = 0; j < WordLength; j++)
			{
				if (i != j && Guess[i] == MyHiddenWord[j])
				{
					BullCowCounter.Cows++;
				}
			}
		}
		// Compare the Letters of the Player's Guess against the Letters of the Hidden Word.
	}

	bMyGameIsWon = (BullCowCounter.Bulls == WordLength);

	return BullCowCounter;
}