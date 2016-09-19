#pragma once

#include <string>

// Unreal friendly syntax
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();
	void Reset();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	// counts bulls & cows, increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyMaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
};