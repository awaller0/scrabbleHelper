#include "scrabbleHelper.h"

int main()
{
    ScrabbleHelper helper;
    helper.readLettersFromUser();
    helper.displayPossibleWords("", "");
    return 0;
}

int ScrabbleHelper::findPrefixIndex(const string &prefix, const vector<string> &words) // Binary search to find the index of the prefix
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
vector<string> ScrabbleHelper::prefixSearchInternal(const string &prefix, const vector<string> &words)
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

ScrabbleHelper::ScrabbleHelper() // constructor
{
    storeAllWords("scrabble_words.csv", validWords);
    storeAllWords("reverse_scrabble_words.csv", reversedValidWords);
}
void ScrabbleHelper::storeAllWords(const string &filename, vector<string> &words) // storing all the words in a vector
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

void ScrabbleHelper::readLettersFromUser()
{
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
void ScrabbleHelper::displayWordsWithPrefix(const string &prefix)
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

void ScrabbleHelper::displayWordsWithSuffix(const string &suffix)
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

void ScrabbleHelper::displayPossibleWords(const string &prefix, const string &suffix)
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

bool ScrabbleHelper::isPossibleWord(const vector<int> &userInputFreq, const vector<int> &wordFreq) 
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

vector<int> ScrabbleHelper::countUserLetters()
{
    // Initialize array with 26 zeros, each index represents a letter from 'a' to 'z'
    vector<int> letterCount(26, 0);

    // Iterate over each letter in the user's input
    for (const string &letter : userLetters)
    {
        // Check if the string is not empty and the first character is a letter
        if (!letter.empty() && isalpha(letter[0]))
        {
            // Convert the first character to lowercase
            char c = tolower(letter[0]);
            // Increment the count for this letter in the frequency array
            letterCount[c - 'a']++;
        }
    }

    // Return the frequency array
    return letterCount;
}

vector<int> ScrabbleHelper::countWordLetters(const string &word)
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