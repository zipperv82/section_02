#include <iostream>
#include<string>
#include"FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;//instantiate new game

int main()
{
	
	bool bPlayAgain = false;
	
	do 
	{
		
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	return 0;
		
}

void PrintIntro() 
{
	// introduce the game
	
	std::cout << std::endl;
	std::cout << "\n\nWelcome to Bulls and Cows a fun word game!\n";
	std::cout << std::endl;
	std::cout << "          }   {          ___" << std::endl;
	std::cout << "          (o o)         (o o)" << std::endl;
	std::cout << "    /------\\ /           \\ /-------\\ " << std::endl;
	std::cout << "   / | BULL|O             O| COW   | \\" << std::endl;
	std::cout << "  *  |-,---|               |-------|  *" << std::endl;
	std::cout << "     ^     ^               ^       ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength()<< " letter isogram I am thinking of?\n";
	return;
}

void PlayGame()
{
	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "\nMax number of Guesses: "<< MaxTries << std::endl;

	// loop for number of guesses while the game is not won
	// there are still tries remaining
	while (!BCGame.IsGameWon()&&BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		
		
		//submit valid guess to game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		//print number of bulls and cows

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		PrintGameSummary();

		
	}
}

FText GetValidGuess( ) 
{
	FText Guess = " ";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "\nTry " << CurrentTry << "of "<< BCGame.GetMaxTries()<<"\nEnter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters\n";
			break;
		case EGuessStatus::OK:
			std::cout << "Good Guess!\n";
			break;
		default:
			break;
			
		}
		

	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{

	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') ||(Response[0]== 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
	
