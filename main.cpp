/* This is the console executable, that makes use of the BullCow class this acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic see the FBullCowGame class. Also this is my first game! 
*/

#include <iostream> //Preprocessor grabs from a file (Importing standard stuff that came with visual studios)
#include <string> //We will be using string so we bring it with the Preprocessor's
#include "FBullCowGame.h" //Tieing the header to the project

using Ftext = std::string; //FString is a changable and mutable object, FText is something that is used for user interaction. We use these for Unreal purposes
using int32 = int;

void PrintIntro(); //Declares the functions or prototypes
void PlayGame();
void PrintGameSummary();
Ftext GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //This is an instance of the class! Instantiate is an instance of a new game. We created an insteand here so we can access anywhere!

int main() //Returning and Int and the name of the method is "main". Close () means its not taking any parameters. For cross platform development you cant use int. 
{
	bool bPlayAgain = false; //Declaring a bool variable this is used for the loop. We use this so we can play again!

	do //We want to play the game first so we are doing a do loop
	{
		PrintIntro(); //Calling the function which introduces the welcome screen
		PlayGame(); //Calling the game function here
		bPlayAgain = AskToPlayAgain(); //This is a returning bool function that will end the do-while loop
	} while	(bPlayAgain); // = True
	

	return 0; //The method returns 0
}

void PrintIntro() 
{
	//Introduces the game
	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength(); //This grabs from our implementation file our word length thats in the function
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done you win!!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries(); //Goes to find the function that returns how many tries the player gets

	//Loop asking for guesses while the game is not won
	//While game is not won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess(); //When GetValidGuess returns an answer it returns it and assigns it to Guess //TODO make loop checking valid

		//EGuessStatus Status = BCGame.CheckGuessValidity;

		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess); //FBullCount is the structure you created and you called it BullCowCount
		
		std::cout << "Bulls = " << BullCowCount.Bulls; //A structure allows you to call on the specefic variable
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

		//TODO add a game summary
	}
	PrintGameSummary();
}

Ftext GetValidGuess() //Loop continually till the user gives a valid guess
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	Ftext Guess = "";//Declared and initialize a Ftext as blank

	do {
		int32 CurrentTry = BCGame.GetCurrentTry(); //Assign the return function a private variable
		std::cout << "Try " << CurrentTry << " out of " << BCGame.GetMaxTries() << "! Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default: //Assuming the Guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //Keep looping till we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word? ";
	Ftext Response = "";
	std::getline(std::cin, Response);

	//To look at the first character its 'variable name[0]'
	//Also you place parenthesis so it reads everything (Response[0] == 'y') not just Response
	std::cout << std::endl;
	return (Response[0] == 'y') ||(Response[0] == 'Y');
}
