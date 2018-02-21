#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//two int initialized to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Invalid_Status
};


class FBullCowGame {
public:
	FBullCowGame();//constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValid(FString) const;
	
	void Reset(); 
	
	//counts bulls and cows and increases try #
	FBullCowCount SubmitValidGuess(FString);


private:
	//see constructor for init
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};