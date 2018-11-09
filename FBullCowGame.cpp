#include "FBullCowGame.h" //Something we made on our own
#include <map>
#define TMap std::map //So whenever we use Tmap it changes to std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries()const 
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry()const 
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

void FBullCowGame::Reset()
{
	bGameIsWon = false;

	constexpr int MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "ant";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1; //Run time values have presidence in the constructor

	return;
}
//Receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount; //The BCC is the struc *type and then name of variable.
	int32 WordLength = MyHiddenWord.length(); //Assuming same length as guess

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; //Increment bulls
				}
				else
				{
					BullCowCount.Cows++; //If not must be a cow
				}
			}
		}
		if (BullCowCount.Bulls == WordLength)
		{
			bGameIsWon = true;
		}
		else
			bGameIsWon = false;
	}
	//Loop through all letters in the guess
		//Compare letters against hidden word
			//Increment bulls if they are in the same place
				//Increments cows if not


		//Compare letters against the hidden word
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//Treat 0 and 1 letter strings as isograms
	if (Word.length() <= 1)
	{
		return true;
	}
	
	TMap <char, bool> LetterSeen; //setup our map. Kind of like an Array
	for (auto Letter : Word) //Stating for all letters of the word. THIS IS A FOREACH IN C++ it is different then C#
	{
		Letter = tolower(Letter); //Lower case everyletter one by one
		if (LetterSeen[Letter]) //Starts at letter one by default it will go false. REMEMBER BOOLEAN INITIALIZE TO FALSE
		{ //
			return false; //We do NOT have an isogram. This is our only return statement
		}
		else 
		{
			LetterSeen[Letter] = true; //If its not in the map
		}

		//Loop through all the letters
			//If the letter is in the map 
				//We do not have an isogram
			//Otherwise we add the letter to the map
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter))//If not a lowercase letter
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsGameWon()const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//If the guess isn't an isogram, return an error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	//If the guess isn't all lowercase, return an error
	//If the guess length is wrong return an error
	//Otherwise return ok
}
