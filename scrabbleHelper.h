#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <fstream>
using namespace std;
#ifndef scrabbleHelper_H
#define scrabbleHelper_H

class ScrabbleHelper
{
private:
    int findPrefixIndex(const string &prefix) // Binary search to find the index of the prefix
    {
        int left = 0;
        int right = validWords.size() - 1;

        while (left <= right)
        {
            int middle = left + (right - left) / 2;

            if (validWords[middle].substr(0, prefix.size()) == prefix)
            {
                return middle; // Found an instance of the prefix
            }
            if (validWords[middle].substr(0, prefix.size()) > prefix)
            {
                right = middle - 1;
            }
            else
            {
                left = middle + 1;
            }
        }
        return -1;
    }
    
    int findSuffixIndex(const string &suffix)
    {
        int left = 0;
        int right = validWords.size() - 1;

        while (left <= right)
        {
            int middle = left + (right - left) / 2;

            if (validWords[middle].substr((validWords[middle].size()-suffix.size()), validWords[middle].size()) == suffix)
            {
                return middle; // Found an instance of the prefix
            }
            if (validWords[middle].substr((validWords[middle].size()-suffix.size()), validWords[middle].size()) > suffix)
            {
                right = middle - 1;
            }
            else
            {
                left = middle + 1;
            }
        }
        return -1; // Prefix not found
    }
    vector<string> validWords;
    vector<string> userLetters;

public:
    ScrabbleHelper() : validWords(), userLetters() {}
    // TODO: correct suffix search by reversing validwords and then searching for the prefix
    // TODO: check if the user's input is valid through checking if the letters are in the alphabet as well as if the letters are in the right format
    // TODO: add function to search if a word contains certain letters in the order typed by the user
    // TODO: add function to seartch if a word ends with certain letters typed by the user

    void readLettersFromUser()
    { // getting the user's letters and storing them in a vector
        cout << "Enter your letters seperate by a space: ";
        string input;
        getline(cin, input);
        istringstream inputStream(input); // using istringstream to seperate the letters
        string currentLetter;
        while (inputStream >> currentLetter)
        { // storing the letters in a the private vector userLetters
            userLetters.push_back(currentLetter);
        }
    }
    vector<string> suffixSearch(const string &suffix){
        vector<string> result;
        int index = findSuffixIndex(suffix);
        if (index == -1){
            return result;
        }
        int i = index;
        while (i >= 0 && validWords[i].substr((validWords[i].size()-suffix.size()), validWords[i].size()) == suffix)
        {
            result.push_back(validWords[i]); // Add all the words to the LEFT(in the arr) with the prefix to the result vector
            i--;
        }

        i = index + 1;
        while (i < validWords.size() && validWords[i].substr((validWords[i].size()-suffix.size()), validWords[i].size()) == suffix)
        {
            result.push_back(validWords[i]); // add all words from the RIGHT(in the arr) with the prefix to the result vector
            i++;
        }

    return result;

    }
    vector<string> prefixSearch(const string &prefix)
    {
        vector<string> result;
        int index = findPrefixIndex(prefix); // Find the index of the prefix
        if (index == -1)
        {
            return result; // return empty vector if prefix not found
        }
        int i = index;
        while (i >= 0 && validWords[i].substr(0, prefix.size()) == prefix)
        {
            result.push_back(validWords[i]); // Add all the words to the LEFT(in the arr) with the prefix to the result vector
            i--;
        }

        i = index + 1;
        while (i < validWords.size() && validWords[i].substr(0, prefix.size()) == prefix)
        {
            result.push_back(validWords[i]); // add all words from the RIGHT(in the arr) with the prefix to the result vector
            i++;
        }

    return result; // Return all the words that have the prefix, empty vector if none
}

void allValidWords()
{ // reads all words from the csv file and stores them in a vector
    ifstream file("scrabble_words.csv");
    if (!file)
    {
        cerr << "Error opening file." << endl;
        return;
    }

    vector<string> words;
    words.reserve(172819); // csv file has 172820 words
    string word;

    while (file >> word)
    { // Read words into the vector
        words.push_back(word);
    }

    file.close();

    validWords = words;
}

void displayWordsWithPrefix(const vector<string> &words)
{
    if (words.empty())
    {
        cout << "No words found with that prefix." << endl;
        return;
    }

    cout << "Words found with that prefix:" << endl;
    for (const auto &word : words)
    {
        cout << word << endl;
    }
}

void displayWordsWithSuffix(const vector<string> &words)
{
    if (words.empty())
    {
        cout << "No words with that suffix" << endl;
        return;
    }

    cout << "Words found with that suffix" << endl;
    for (const auto &word : words)
    {
        cout << word << endl;
    }
}

};
#endif