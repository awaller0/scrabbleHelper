#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <fstream>
using namespace std;

class ScrabbleHelper
{

private:
    vector<string> validWords;
    vector<string> letters;

public:
    ScrabbleHelper() {}

    // TODO: check if the user's input is valid through checking if the letters are in the alphabet as well as if the letters are in the right format

    void readLettersFromUser()
    { // getting the user's letters and storing them in a vector
        bool check;
        string input;
        cout << "Enter your letters seperate by a space: ";
        getline(cin, input);

        istringstream inputStream(input); // using istringstream to seperate the letters
        string currentLetter;

        while (inputStream >> currentLetter)
        { // storing the letters in a vector
            letters.push_back(currentLetter);
        }
    }

    vector<string> prefixSearch(const string &prefix)
    { // Binary search function for finding the prefix to a word
        int left = 0;
        int right = validWords.size() - 1;
        vector<string> result;

        while (left <= right)
        {
            int middle = left + (right - left) / 2;

            if (validWords[middle].substr(0, prefix.size()) == prefix)
            {
                int i = middle; // Prefix found
                while (i >= 0 && validWords[i].substr(0, prefix.size()) == prefix)
                {
                    result.push_back(validWords[i]); // Add all the words to the LEFT(in the arr) with the prefix to the result vector
                    i--;
                }

                i = middle + 1;
                while (i < validWords.size() && validWords[i].substr(0, prefix.size()) == prefix)
                {
                    result.push_back(validWords[i]); // add all words from the RIGHT(in the arr) with the prefix to the result vector
                    i++;
                }
            }

            if (validWords[middle].substr(0, prefix.size()) > prefix)
            { // If the target is smaller, search the left half
                right = middle - 1;
            }

            else
            { // If the target is larger, search the right half
                left = middle + 1;
            }
        }
        return result; // Return all the words that have the prefix, empty vector if none
    }

    void getAllValidWords()
    { //reads all words from the csv file and stores them in a vector
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

void displayWordsWithPrefix(const vector<string>& words)
{
    if (words.empty())
    {
        cout << "No words found with that prefix." << endl;
        return;
    }

    cout << "Words found with that prefix:" << endl;
    for (const auto& word : words)
    {
        cout << word << endl;
    }
}
};

int main()
{
    ScrabbleHelper helper;

    helper.getAllValidWords();
    helper.displayWordsWithPrefix(helper.prefixSearch("awa"));
    return 0;
}
