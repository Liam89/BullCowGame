/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class
*/

#include "FBullCowGame.h"

#include <iostream>
#include <string>

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main()
{
	PrintIntro();

	do {
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

// Introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations, you win!\n";
	}
	else {
		std::cout << "Unlucky, you lose.\n";
	}
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset();
	auto MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < MaxTries) {
		auto Guess = GetValidGuess();

		auto BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << ".\n";
		std::cout << std::endl;
	}

	PrintGameSummary();
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess;
	auto Status = EGuessStatus::Invalid;
	do {
		auto CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Guess must contain only lower case characters\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Guess not an isogram (must not contain duplicate letters)\n\n";
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response;
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
