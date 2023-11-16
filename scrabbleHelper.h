#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <fstream>
#include <algorithm>
#ifndef SCRABBLEHELPER_H
#define SCRABBLEHELPER_H

class ScrabbleHelper
{
private:
    std::vector<std::string> validWords;
    std::vector<std::string> reversedValidWords;
    std::vector<std::string> userLetters;

    // Binary search to find the index of the prefix
    int findPrefixIndex(const std::string &prefix, const std::vector<std::string> &words);

    // Return all the words that have the prefix, empty vector if none
    std::vector<std::string> prefixSearchInternal(const std::string &prefix, const std::vector<std::string> &words);

public:
    ScrabbleHelper();

    // storing all the words in a vector
    void storeAllWords(const std::string &filename, std::vector<std::string> &words);

    // getting the user's letters and storing them in a vector
    void readLettersFromUser();

    // displaying all the words that contain the prefix
    void displayWordsWithPrefix(const std::string &prefix);

    // displaying all the words that contain the suffix
    void displayWordsWithSuffix(const std::string &suffix);

    // displaying all the words that contain the prefix and suffix with the user's letters
    void displayPossibleWords(const std::string &prefix, const std::string &suffix);

    // Checks if a word can be formed from the user's input by comparing frequency of each letter.
    bool isPossibleWord(const std::vector<int> &userInputFreq, const std::vector<int> &wordFreq);

    // Counts the frequency of each letter in the user's input
    std::vector<int> countUserLetters();

    // Counts the frequency of each letter in a word
    std::vector<int> countWordLetters(const std::string &word);
};

#endif // SCRABBLEHELPER_H
