#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame(){Reset();}


int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const 
{
	TMap <int32, int32> WordLengthToMaxTries{ {3,5}, {4,5},{5,5},{6,5} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "ant";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//receives a valid guess, increments turn and shows results
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
		
	MyCurrentTry++;
	FBullCowCount BullCowCount;
int32 WordLength = MyHiddenWord.length();//assumes same length as hidden word

	//loop through all letters in hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		//compare letters against guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{//if they match then
				if (MHWChar == GChar) 
				{//if they are in the same spot
					BullCowCount.Bulls++; //increment bulls
				}
				else 
				{
					BullCowCount.Cows++;//increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	//setup map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else
		{
			LetterSeen[Letter] = true;
		}

	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

	EGuessStatus FBullCowGame::CheckGuessValid(FString Guess) const
{
	if (!IsIsogram(Guess))//if the guess isn't isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))	//if the guess isn't lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength() ) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else //otherwise
	{
		return EGuessStatus::OK;
	}

}
