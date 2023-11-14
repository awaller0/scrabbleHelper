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

// TODO: check if the user's input is valid through checking if the letters are in the alphabet as well as if the letters are in the right format
// TODO: add function to search if a word contains certain letters in the order typed by the user
// TODO: add function that takes 3 arguements, the user's letters, the prefix, and the suffix and returns all the words that contain the prefix and suffix with the user's letters
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
        string reversedSuffix = string(suffix.rbegin(), suffix.rend());                  // Reverse the suffix EX: user: ing, reversedSuffix://
        vector<string> words = prefixSearchInternal(reversedSuffix, reversedValidWords); // gni, since the words are stored in reverse order //
        if (words.empty())
        {
            cout << "No words with that suffix" << endl;
            return;
        }

        cout << "Words found with that suffix" << endl;
        for (const auto &word : words)
        {
            string reversedWord = string(word.rbegin(), word.rend()); // reversing the words back to normal
            cout << reversedWord << endl;                             // printing the words
        }
    }

    void displayPossibleWords(const string &prefix, const string &suffix)
    {
        // Step 1: Find all words with the given prefix.
        vector<string> prefixWords = prefixSearchInternal(prefix, validWords);

        // Step 2: Find all words with the given suffix, using reversed order search.
        string reversedSuffix = string(suffix.rbegin(), suffix.rend());
        vector<string> suffixWordsTemp = prefixSearchInternal(reversedSuffix, reversedValidWords);
        vector<string> suffixWords; // This will store the suffix words in the correct order.

        for (auto &word : suffixWordsTemp)
        {
            suffixWords.push_back(string(word.rbegin(), word.rend()));
        }
        // Step 3: Sort the two vectors.
        sort(prefixWords.begin(), prefixWords.end());
        sort(suffixWords.begin(), suffixWords.end());

        // Step 4: Intersect the two vectors.
        vector<string> commonWords;


        set_intersection(prefixWords.begin(), prefixWords.end(),
                         suffixWords.begin(), suffixWords.end(),
                         back_inserter(commonWords));



        vector<int> userInputFreq = countUserLetters();
        vector<string> possibleWords;

        for (const string &word : commonWords)
        { // Assume validWords is your list of valid Scrabble words
            vector<int> wordFreq = countWordLetters(word);

            if (isPossibleWord(userInputFreq, wordFreq))
            {
                possibleWords.push_back(word);
            }
        }
        sort(possibleWords.begin(), possibleWords.end());
        // Display the possible words
        for (const string &word : possibleWords)
        {
            cout << word << endl;
        }
    }

    bool isPossibleWord(const vector<int> &userInputFreq, const vector<int> &wordFreq)
    {
        for (int i = 0; i < 26; i++)
        {
            if (userInputFreq[i] < wordFreq[i])
            {
                return false;
            }
        }
        return true;
    }

    vector<int> countUserLetters()
    {
        vector<int> letterCount(26, 0); // Initialize array with 26 zeros

        for (const string &letter : userLetters)
        {
            if (!letter.empty() && isalpha(letter[0]))
            {                                // Check if the string is not empty and the first character is a letter
                char c = tolower(letter[0]); // Convert the first character to lowercase
                letterCount[c - 'a']++;      // Increment the count for this letter
            }
        }

        return letterCount;
    }
    vector<int> countWordLetters(const string &word)
    {
        vector<int> letterCount(26, 0); // Initialize array with 26 zeros

        for (char c : word)
        {
            if (isalpha(c))
            {
                c = tolower(c);         // Convert to lowercase
                letterCount[c - 'a']++; // Increment the count
            }
        }

        return letterCount;
    }
};
#endif