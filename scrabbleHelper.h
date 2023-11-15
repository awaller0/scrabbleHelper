#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <fstream>
#include <algorithm>
using namespace std;
#ifndef scrabbleHelper_H
#define scrabbleHelper_H


class ScrabbleHelper
{
private:
    vector<string> validWords;
    vector<string> reversedValidWords;
    vector<string> userLetters;

    // Binary search to find the index of the prefix
    int findPrefixIndex(const string &prefix, const vector<string> &words); 

    // Return all the words that have the prefix, empty vector if none
    vector<string> prefixSearchInternal(const string &prefix, const vector<string> &words);

public:
    ScrabbleHelper();

    // storing all the words in a vector
    void storeAllWords(const string &filename, vector<string> &words); 
 
    // getting the user's letters and storing them in a vector
    void readLettersFromUser();

    // displaying all the words that contain the prefix
    void displayWordsWithPrefix(const string &prefix);

    // displaying all the words that contain the suffix
    void displayWordsWithSuffix(const string &suffix);

    // displaying all the words that contain the prefix and suffix with the user's letters
    void displayPossibleWords(const string &prefix, const string &suffix);

    // Checks if a word can be formed from the user's input by comparing frequency of each letter.
    bool isPossibleWord(const vector<int> &userInputFreq, const vector<int> &wordFreq);

    // Counts the frequency of each letter in the user's input
    vector<int> countUserLetters();

    // Counts the frequency of each letter in a word
    vector<int> countWordLetters(const string &word);
};
#endif