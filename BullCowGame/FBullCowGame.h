/* 
This is the  Bulls Cows Game Logic (No View Code or Direct User Interaction)
The Game is a Simple Word Guess Game based on Mastermind
*/

#pragma once

#include <string>
#include <map>

// Unreal Friendly Syntax
#define TMap std::map
using FString = std::string;
using int32 = int;


struct FBullCowCounter
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Uninitialized,
	Ok,
	NotOk_Isogram,
	NotOk_Length,
	NotOk_UpperCase
};

class FBullCowGame
{
public:
	FBullCowGame(); // Default Constructor
	~FBullCowGame(); // Default Destructor

	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus IsValidGuess(FString) const;

	void Reset();
	FBullCowCounter SubmitValidGuess(FString);

private:
	// See Constructor for Initialization.
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bMyGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};