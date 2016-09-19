#include "FBullCowGame.h"

#include <algorithm>
#include <map>

namespace {
	bool IsIsogram(FString Guess);
}

FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "and";
	constexpr int32 MAX_TRIES = 8;

	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	bGameWon = false;
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.size(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }


int32 FBullCowGame::GetMaxTries() const { 
	return static_cast<int32>(2 + pow(1.5, GetHiddenWordLength()));
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.size() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else if (!std::all_of(Guess.begin(), Guess.end(), [](char c) { return islower(c); })) {
		return EGuessStatus::Not_Lowercase;
	}
	else {
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns cout
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	++MyCurrentTry;
	FBullCowCount BullCowCount;

	int32 WordLength = Guess.size();
	for (auto i = 0; i < WordLength; ++i)
	{
		for (auto j = 0; j < WordLength; ++j)
		{
			if (Guess[i] == MyHiddenWord[j]) {
				if (i == j) {
					++BullCowCount.Bulls;
				}
				else {
					++BullCowCount.Cows;
				}
			}
		}
	}

	bGameWon = BullCowCount.Bulls == WordLength;

	return BullCowCount;
}

namespace {
	bool IsIsogram(FString Guess) {
		std::map<char, int> seen_letters;
		for (auto c : Guess) {
			auto count = ++seen_letters[tolower(c)];
			if (count > 1) {
				return false;
			}
		}
		return true;
	}
}