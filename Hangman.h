#ifndef _Hangman_

#define _Hangman_

#include<iostream>
#include<map>

using namespace std;

class Hangman {
    
    private:
    string toLower(string word);
    void setAllowedChars();
    void fillDictionary(string fileName);
    
    map<int, string> words;
    map<char, bool> letters;
    string currentWord;
    int attempts;
    int allowedAttempts;
    
    public:
    Hangman(string fileName);
    string wordPlaceholder();
    bool isFinished() const;
    bool isHanged() const;
    bool hasWon() const;
    bool isAllowedInput(char input);
    bool wordContainsChar(char input);
    int count() const;
    void restart();
    void addGuess(char guess);
    void incrementAttempts();
    void getRandomWord();
    void printTitle();
    void printRules();
    void printResult();
    
    string userGuess;
    
};

#endif // _Hangman_