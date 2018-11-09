#pragma once //Making sure everything is just imported once
//Header is the thing that we declared our functions at the top of our cpp similar
#include <string>

using FString = std::string;
using int32 = int;

//Never use namespace in a headerfile, maybe just never use it...

//All values initialized to 0
struct FBullCowCount //Everything is public in a struct
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus //Value list. This is for validating
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame
{
public: 
	FBullCowGame(); //Constructor
	int32 GetMaxTries() const; //Return an int32
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; //Struc that takes in a string and returns a pair

	void Reset(); //TODO make a more rich return value

	FBullCowCount SubmitValidGuess(FString);

//Please try and ignore this and focus on the interface above ^^
private: //You want private variables so the variables are specific to the instances
	int32 MyCurrentTry; //Compiler time values/See constructor for intialization
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString)const;
	bool IsLowerCase(FString)const;
};
