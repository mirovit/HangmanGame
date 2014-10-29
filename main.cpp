#include<iostream>
#include<string>
#include "Hangman.h"

using namespace std;

void runGame(Hangman& Game);

int main()
{
    Hangman Game("fruits.txt");
    
    Game.printTitle();
    
    Game.printRules();

    char runAnotherGame;
    bool run = true;
    
    while( run )
    {
		try {
			runGame(Game);
        } catch(...){}
		
        cout << "Play another game? (y/n): ";
        cin >> runAnotherGame;
        
        if( runAnotherGame != 'y' && runAnotherGame != 'Y' )
        {
            run = false;
        }
        
        cout << endl;
    }
    
    return 0;
}

void runGame(Hangman& Game)
{
    Game.restart();
    
    Game.getRandomWord();
    
    cout << Game.wordPlaceholder() << endl << endl;
    
    char guess;
    
    while( !Game.isFinished() )
    {
        cout << "Enter a guess: ";
        cin >> guess;
        
        if( !Game.isAllowedInput(guess) )
        {
            cout << "Your guess is not allowed. Try again." << endl;
        }
            
        if( Game.isAllowedInput(guess) && !Game.wordContainsChar(guess) )
        {
            Game.incrementAttempts();
            cout << "Wrong guess. Try again." << endl;
        }
        
        if( Game.isAllowedInput(guess) && Game.wordContainsChar(guess) )
        {
            Game.addGuess(guess);
        }

        cout << Game.userGuess << endl;
    }
    
    Game.printResult();
}