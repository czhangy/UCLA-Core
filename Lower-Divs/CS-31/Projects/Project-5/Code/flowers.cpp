//
//  main.cpp
//  flowers
//
//  Created by Charles Zhang on 11/9/19.
//  Copyright © 2019 Charles Zhang. All rights reserved.
//

#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

const char WORDFILENAME[] = "/Users/charleszhang/Desktop/text.txt";
const int MAXWORDS = 10000;

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);

int main()
{
    char wordList[MAXWORDS][MAXWORDLEN+1];
    int actualNum = getWords(wordList, MAXWORDS, WORDFILENAME);
    
    if (actualNum < 1) { // terminates program
        cout << "No words were loaded, so I can't play the game." << endl;
        return 1;
    }
    
    int numRounds;
    cout << "How many rounds do you want to play? ";
    cin >> numRounds;
    cin.ignore(10000, '\n');
    if (numRounds < 1) { // terminates program
        cout << "The number of rounds must be positive." << endl;
        return 1;
    }
    
    double totalScore = 0;
    int max = 0;
    int min = 0;
    for (int i = 0; i < numRounds; i++) {
        int wordNum = randInt(0, actualNum - 1);
        cout << endl;
        cout << "Round " << i + 1 << endl;
        cout << "The mystery word is " << strlen(wordList[wordNum]) << " letters long." << endl;
        int numTries = playOneRound(wordList, actualNum, wordNum);
        if (numTries == 1) {
            cout << "You got it in 1 try." << endl;
        } else {
            cout << "You got it in " << numTries << " tries." << endl;
        }
        if (i == 0) {
            max = numTries;
            min = numTries;
        } else {
            if (numTries > max) {
                max = numTries;
            }
            if (numTries < min) {
                min = numTries;
            }
        }
        totalScore += numTries;
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << totalScore / (i + 1) << ", minimum: " << min << ", maximum: " << max << endl;
    }
}

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum) {
    if (nWords < 1 || wordnum < 0 || wordnum >= nWords) {
        return -1;
    }
    char trialWord[100] = "";
    int numFlowers;
    int numBees;
    int score = 0;
    while (trialWord != words[wordnum]) { // trialword is changed after the condition is checked
        bool validWord = false;
        bool lowercaseLetters = true;
        numFlowers = 0;
        numBees = 0;
        cerr << wordnum << endl;
        cerr << words[wordnum] << endl;
        cout << "Trial word: ";
        cin.getline(trialWord, 100);
        size_t trialLength = strlen(trialWord);
        if (trialLength < 4 || trialLength > 6) { // checks for correct length
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        for (int i = 0; trialWord[i] != '\0'; i++) {
            if (isupper(trialWord[i]) || ! isalpha(trialWord[i])) { // checks if lowercase and if letter
                cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
                lowercaseLetters = false;
                break;
            }
        }
        if (! lowercaseLetters) {
            continue;
        }
        for (int i = 0; i < nWords; i++) { // checks if word is in the array
            if (strcmp(trialWord, words[i]) == 0) {
                validWord = true;
                break;
            }
        }
        if (! validWord) { // error message for unknown word
            cout << "I don't know that word." << endl;
            continue;
        }
        score++; // score increment
        if (strcmp(trialWord, words[wordnum]) == 0) { // returns score when guess is correct
            return score;
        }
        char correctWord[MAXWORDLEN];
        strcpy(correctWord, words[wordnum]);
        for (int i = 0; trialWord[i] != '\0'; i++) { // loops until one of the words runs out
            for (int j = 0; correctWord[j] != '\0'; j++) {
                if (trialWord[i] == correctWord[j]) {
                    if (i == j) {
                        numFlowers++;
                    } else {
                        numBees++;
                    }
                    trialWord[i] = ' ';
                    correctWord[j] = ' ';
                    break;
                }
            }
        }
        cout << "Flowers: " << numFlowers << ", Bees: " << numBees << endl;
    }
    return score;
}


