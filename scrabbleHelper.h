#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <fstream>
using namespace std;
#ifndef scrabbleHelper_H
#define scrabbleHelper_H

// TODO: check if the user's input is valid through checking if the letters are in the alphabet as well as if the letters are in the right format
// TODO: add function to search if a word contains certain letters in the order typed by the user

class ScrabbleHelper
{
private:
    vector<string> validWords;
    vector<string> reversedValidWords;
    vector<string> userLetters;

    int findPrefixIndex(const string &prefix, const vector<string> &words) // Binary search to find the index of the prefix
    {
        int left = 0;
        int right = validWords.size() - 1;

        while (left <= right)
        {
            int middle = left + (right - left) / 2;

            if (words[middle].substr(0, prefix.size()) == prefix)
            {
                return middle; // Found an instance of the prefix
            }
            if (words[middle].substr(0, prefix.size()) > prefix)
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
    vector<string> prefixSearchInternal(const string &prefix, const vector<string> &words)
    {
        vector<string> result;
        int index = findPrefixIndex(prefix, words); // Find the index of the prefix
        if (index == -1)
        {
            return result; // return empty vector if prefix not found
        }
        int i = index;
        while (i >= 0 && words[i].substr(0, prefix.size()) == prefix)
        {
            result.push_back(words[i]); // Add all the words to the LEFT(in the arr) with the prefix to the result vector
            i--;
        }

        i = index + 1;
        while (i < words.size() && words[i].substr(0, prefix.size()) == prefix)
        {
            result.push_back(words[i]); // add all words from the RIGHT(in the arr) with the prefix to the result vector
            i++;
        }

        return result; // Return all the words that have the prefix, empty vector if none
    }

public:
    ScrabbleHelper() // constructor
    {
        storeAllWords("scrabble_words.csv", validWords);
        storeAllWords("reverse_scrabble_words.csv", reversedValidWords);
    }

    void storeAllWords(const string &filename, vector<string> &words) //
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        words.clear();
        words.reserve(172819);
        string word;

        while (file >> word)
        {
            words.push_back(word);
        }
        file.close();
    }

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

    void displayWordsWithPrefix(const string &prefix)
    {
        vector<string> words = prefixSearchInternal(prefix, validWords);
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

    void displayWordsWithSuffix(const string &suffix)
    {
        string reversedSuffix = string(suffix.rbegin(), suffix.rend());          // Reverse the suffix EX: user: ing, reversedSuffix://
        vector<string> words = prefixSearchInternal(reversedSuffix, reversedValidWords); // gni, since the words are stored in reverse order//
        if (words.empty())
        {
            cout << "No words with that suffix" << endl;
            return;
        }

        cout << "Words found with that suffix" << endl;
        for (const auto &word : words)
        {
            string reversdWord = string(word.rbegin(), word.rend()); // reversing the words back to normal
            cout << reversdWord << endl;
        }
    }
};
#endif