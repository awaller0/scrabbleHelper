#include "scrabbleHelper.h"
#include <vector>
int main()
{
    ScrabbleHelper helper;
    helper.readLettersFromUser();
    helper.displayPossibleWords("", "");
    return 0;
}

int ScrabbleHelper::findPrefixIndex(const std::string &prefix, const std::vector<std::string> &words) // Binary search to find the index of the prefix
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
std::vector<std::string> ScrabbleHelper::prefixSearchInternal(const std::string &prefix, const std::vector<std::string> &words)
{
    std::vector<std::string> result;
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
void ScrabbleHelper::storeAllWords(const std::string &filename, std::vector<std::string> &words) // storing all the words in a vector
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    words.clear();
    words.reserve(172819);
    std::string word;

    while (file >> word)
    {
        words.push_back(word);
    }
    file.close();
}

void ScrabbleHelper::readLettersFromUser()
{
    std::cout << "Enter your letters seperate by a space: ";
    std::string input;
    getline(std::cin, input);
    std::istringstream inputStream(input); // using istringstream to seperate the letters
    std::string currentLetter;
    while (inputStream >> currentLetter)
    { // storing the letters in a the private vector userLetters
        userLetters.push_back(currentLetter);
    }
}
void ScrabbleHelper::displayWordsWithPrefix(const std::string &prefix)
    {
        std::vector<std::string> words = prefixSearchInternal(prefix, validWords);
        if (words.empty())
        {
            std::cout << "No words found with that prefix." << std::endl;
            return;
        }

        std::cout << "Words found with that prefix:" << std::endl;
        for (const auto &word : words)
        {
            std::cout << word << std::endl;
        }
    }

void ScrabbleHelper::displayWordsWithSuffix(const std::string &suffix)
    {
        std::string reversedSuffix = std::string(suffix.rbegin(), suffix.rend());                  // Reverse the suffix EX: user: ing, reversedSuffix://
        std::vector<std::string> words = prefixSearchInternal(reversedSuffix, reversedValidWords); // gni, since the words are stored in reverse order //
        if (words.empty())
        {
            std::cout << "No words with that suffix" << std::endl;
            return;
        }

        std::cout << "Words found with that suffix" << std::endl;
        for (const auto &word : words)
        {
            std::string reversedWord = std::string(word.rbegin(), word.rend()); // reversing the words back to normal
            std::cout << reversedWord << std::endl;                             // printing the words
        }
    }

void ScrabbleHelper::displayPossibleWords(const std::string &prefix, const std::string &suffix)
    {
        // Step 1: Find all words with the given prefix.
        std::vector<std::string> prefixWords = prefixSearchInternal(prefix, validWords);

        // Step 2: Find all words with the given suffix, using reversed order search.
        std::string reversedSuffix = std::string(suffix.rbegin(), suffix.rend());
        std::vector<std::string> suffixWordsTemp = prefixSearchInternal(reversedSuffix, reversedValidWords);
        std::vector<std::string> suffixWords; // This will store the suffix words in the correct order.

        for (auto &word : suffixWordsTemp)
        {
            suffixWords.push_back(std::string(word.rbegin(), word.rend()));
        }
        // Step 3: Sort the two vectors.
        sort(prefixWords.begin(), prefixWords.end());
        sort(suffixWords.begin(), suffixWords.end());

        // Step 4: Intersect the two vectors.
        std::vector<std::string> commonWords;


        set_intersection(prefixWords.begin(), prefixWords.end(),
                         suffixWords.begin(), suffixWords.end(),
                         back_inserter(commonWords));



        std::vector<int> userInputFreq = countUserLetters();
        std::vector<std::string> possibleWords;

        for (const std::string &word : commonWords)
        { // Assume validWords is your list of valid Scrabble words
            std::vector<int> wordFreq = countWordLetters(word);

            if (isPossibleWord(userInputFreq, wordFreq))
            {
                possibleWords.push_back(word);
            }
        }
        sort(possibleWords.begin(), possibleWords.end());
        // Display the possible words
        for (const std::string &word : possibleWords)
        {
            std::cout << word << std::endl;
        }
    }

bool ScrabbleHelper::isPossibleWord(const std::vector<int> &userInputFreq, const std::vector<int> &wordFreq) 
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

std::vector<int> ScrabbleHelper::countUserLetters()
{
    // Initialize array with 26 zeros, each index represents a letter from 'a' to 'z'
    std::vector<int> letterCount(26, 0);

    // Iterate over each letter in the user's input
    for (const std::string &letter : userLetters)
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

std::vector<int> ScrabbleHelper::countWordLetters(const std::string &word)
    {
        std::vector<int> letterCount(26, 0); // Initialize array with 26 zeros

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