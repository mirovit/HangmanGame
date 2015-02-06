#include<iostream>
#include<locale>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include "Hangman.h"
#include "RuntimeExceptions.h"

using namespace std;

/**
 * Constructor
 * 
 * Load Hangman from file.
 */
Hangman::Hangman(string fileName)
{
	words.reserve(110000);

	fillDictionary(fileName);

	setAllowedChars();

    attempts = 0;
    allowedAttempts = 5;
};

/**
 * Get a random word from the loaded Hangman.
 */
void Hangman::getRandomWord()
{
	if (words.size() == 0)
	{
		throw RuntimeException("Game was not loaded properly. Cannot continue.");
	}

    srand(time(NULL));

	int index = rand() % words.size() + 1;
    
    currentWord = words[index];
};

/**
 * Tranform a word to lowercase.
 */
string Hangman::toLower(string word)
{
  locale loc;
  string wordToLower;
  
  for (string::size_type i=0; i < word.length(); ++i)
  {
    wordToLower += tolower(word[i], loc);
  } 
  
  return wordToLower;
};

/**
 * Generate a placehoder for the word.
 */
string Hangman::wordPlaceholder()
{
    string placehoder;
    
    for(unsigned int i = 0; i < currentWord.length(); i++)
    {
        if( currentWord[i] >= 'a' && currentWord[i] <= 'z' )
        {
            placehoder += "*";
        } else {
            placehoder += currentWord[i];
        }
    }
    
    userGuess = placehoder;
    
    return placehoder;
};

/**
 * Whether the current game has finished.
 */
bool Hangman::isFinished() const
{
    return isHanged() || hasWon();
};

/**
 * Whether the player has been hanged.
 */
bool Hangman::isHanged() const
{
    return (attempts == allowedAttempts && currentWord != userGuess);
};

/**
 * Whether the player won the game.
 */
bool Hangman::hasWon() const
{
    return !isHanged() && currentWord == userGuess;
};

/**
 * Check the input of the player for illegal characters.
 */
bool Hangman::isAllowedInput(char input)
{
    return (letters[input] == true) ? true : false;
};

/**
 * Check if the current word contains the guess of the player.
 */
bool Hangman::wordContainsChar(char input)
{
    return currentWord.find(input) != string::npos;
};

/**
 * Add the guessed character.
 */
void Hangman::addGuess(char guess)
{
    for(unsigned int i = 0; i < currentWord.length(); i++)
    {
        if(currentWord[i] == guess)
        {
            userGuess[i] = guess;
        }
    }
};

/**
 * Increment the attempts for guessing the word.
 */
void Hangman::incrementAttempts()
{
    attempts += 1;
};

/**
 * Set the allowed chars for a guess.
 */
void Hangman::setAllowedChars()
{
    for(char i = 'a'; i <= 'z'; i++)
    {
        letters.insert( pair<char, bool>(i, true) );
    }
};

/**
 * Fill the dictonary from a file.
 */
void Hangman::fillDictionary(string fileName)
{
    ifstream file( fileName.c_str() );
    string word;

	if (!file.good())
		throw FileDoesnotExist("The dictionary could not be loaded. Please make sure that '" + fileName + "' exists.");
    
	if( file.is_open() )
    {
        while(getline(file, word))
        {
            word = toLower(word);
			words.push_back(word);
        }
        
        file.close();
    }
};

/**
 * Restart the attempts counter.
 */
void Hangman::restart()
{
    attempts = 0;
};

/**
 * Print game title.
 */
void Hangman::printTitle()
{
    cout << "Welcome to Hangman!" << endl << endl;
};

/**
 * Print the rules of the game.
 */
void Hangman::printRules()
{
    cout << "Here's how to play:" << endl;
    cout << "1. You will see a placehoder of the word you have to guess, so you'll know how many letters it has." << endl;
    cout << "2. You will be prompted to enter a guess. Your guess should be from the letters a through z in small caps." << endl;
    cout << "3. If you enter an illegal character, you will be notified that it is not valid and will be prompted to enter a new one. You won't lose point for this." << endl;
    cout << "4. When you enter a valid guess, if the letter is contained it will be filled in all spaces it appears, if it is not contained you will lose a point." << endl;
    cout << "5. The game ends if you enter 5 wrong guesses or you guess the word." << endl << endl;
    cout << "May the odds be ever in your favour!" << endl << endl;
};

/**
 * Print the end result of the current game.
 */
void Hangman::printResult()
{
    if( isHanged() )
    {
        cout << endl << "You lost. The word was " << currentWord << endl;
    }
    
    if( hasWon() )
    {
        cout << endl << "Yay! You won!" << endl;
    }
};