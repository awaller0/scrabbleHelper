#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <fstream>
using namespace std;




class ScrabbleHelper {

private:
    vector<string> validWords;
    vector<string> letters;
public:
    ScrabbleHelper() {}

    //TODO: check if the user's input is valid through checking if the letters are in the alphabet as well as if the letters are in the right format


    void getLetters() {                                     //getting the user's letters and storing them in a vector
        bool check;
        string input;
        cout << "Enter your letters seperate by a space: ";     
        getline(cin, input);
        
        
            istringstream  iss(input);                          //using istringstream to seperate the letters
            string letter;

            while (iss >> letter) {                             //storing the letters in a vector
                letters.push_back(letter);
            }
        }

       
    vector<string> prefixSearch(const string& prefix) {  // Binary search function for finding the prefix to a word
    
    int left = 0;
    int right = validWords.size() - 1;
    vector <string> result;

    while (left <= right) {
        int middle = left + (right - left) / 2;


        if (validWords[middle].substr(0,prefix.size()) == prefix) { 
            int i = middle; // Prefix found
            while (i >= 0 && validWords[i].substr(0,prefix.size()) == prefix) {
                result.push_back(validWords[i]); // Add all the words to the LEFT(in the arr) with the prefix to the result vector
                i--;
            }
            i = middle + 1;
            while (i < validWords.size() && validWords[i].substr(0,prefix.size()) == prefix) {
                result.push_back(validWords[i]); // add all words from the RIGHT(in the arr) with the prefix to the result vector
                i++;
            }
        }

        // If the target is smaller, search the left half
        if (validWords[middle].substr(0,prefix.size()) > prefix) {
            right = middle - 1;
        }
        // If the target is larger, search the right half
        else {
            left = middle + 1;
        }
    }

    return result; // Return all the words that have the prefix, empty vector if none
}

    void displayLetters(){
            cout << "Your letters are: ";
            for(int i = 0; i < letters.size(); i++){
                cout << letters[i] << " ";
            }
        }

    void getAllValidWords() {
            ifstream file("scrabble_words.csv");
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    vector<string> words;
    words.reserve(172819);
    string word;

    // Read words into the vector
    while (file >> word) {
        words.push_back(word);
    }

    file.close();

    validWords = words;
    }

    void displayValidWords() {
        for (int i = 0; i < validWords.size(); i++) {
            cout << validWords[i] << endl;
        }
    }
};

int main() {
    ScrabbleHelper helper;

    helper.getAllValidWords();
    vector<string> wordsWithPrefix = helper.prefixSearch("boy");

    for (int i = 0; i < wordsWithPrefix.size(); i++) {
        cout << wordsWithPrefix[i] << endl;
    }
    return 0;
}



