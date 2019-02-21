/* 
This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern 
and is responsible for ALL user interaction.
For game logic see the FBullCowGame class.
*/

// TODO: Create Lists of Isograms for Different Difficulties)
// TODO: Create Levels of Difficult (Easy, Medium, Hard)
// TODO: Link the Level of Difficult to the Correct List of the Words
// TODO: Improve the Number of Max Tries Criteria

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Unreal Friendly Syntax
using FText = std::string;
using int32 = int;

// Function Prototypes
void PrintIntroduction();
void PlayGame();
void PrintGuess(FText);
bool bPlayAgain();
FText GetValidGuess();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiates a New Game, which is re-used across multiple plays.

int main()
{
	PrintIntroduction();

	PlayGame();

	return 0;
}

void PrintIntroduction()
{
	std::cout << "########################################\n";
	std::cout << "# Welcome to Bulls and Cows Word Game! #\n";
	std::cout << "########################################\n";
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "\nCan you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";

	return;
}

void PlayGame()
{
	// Ask for Guesses while the Game is NOT won or while there are still Tries Remaining
	do
	{
		BCGame.Reset();

		int32 MaxTries = BCGame.GetMaxTries();
		while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
		{
			FText ValidGuess = GetValidGuess();

			// Submit Valid Guess to the Game and Receives Bulls & Cows Counter.
			FBullCowCounter BullCowCounter = BCGame.SubmitValidGuess(ValidGuess);
			// Print Number of Bulls and Cows
			std::cout << "Bulls = " << BullCowCounter.Bulls;
			std::cout << ";Cows = " << BullCowCounter.Cows << std::endl;
		}

		PrintGameSummary();

	} while (bPlayAgain());

	return;
}

// Loops Indefinitely until Gets a Valid Guess from the Player
FText GetValidGuess()
{
	FText Guess = "";

	EGuessStatus GuessStatus = EGuessStatus::Uninitialized;
	do
	{
		// Get a Guess from the Player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries() << " => Enter you guess: ";
		std::getline(std::cin, Guess);

		// Check whether the Guess is Valid and Print a Message to STD Output if the Guess isn't Valid.
		GuessStatus = BCGame.IsValidGuess(Guess);
		switch (GuessStatus)
		{
		case EGuessStatus::NotOk_Isogram:
			std::cout << "Please, Enter a Word without Repeating Letters.\n";
			break;

		case EGuessStatus::NotOk_Length:
			std::cout << "Please, Enter a " << BCGame.GetHiddenWordLength() << " Letter(s) Word.\n";
			break;

		case EGuessStatus::NotOk_UpperCase:
			std::cout << "Please, Enter only Lowercase Letters.\n";
			break;

		default:
			break;
		}

	} while (GuessStatus != EGuessStatus::Ok);

	return Guess;
}

// Loops Indefinitely until Gets a Valid Answer from the Player
bool bPlayAgain()
{
	std::cout << "\nWould you like to play again with the same word (y/n)?";

	FText Answer = "";
	std::getline(std::cin, Answer);

	if (Answer[0] == 'y' || Answer[0] == 'Y')
	{
		return true;
	}
	else if (Answer[0] == 'n' || Answer[0] == 'N')
	{
		return false;
	}

	return bPlayAgain();
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nCongratulations, You Won!";
	}
	else
	{
		std::cout << "\nBetter Luck Next Time.";
	}
}