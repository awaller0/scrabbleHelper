#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

// Binary search function
bool prefixSearch(const std::vector<std::string>& words, const std::string& prefix) {
    int left = 0;
    int right = words.size() - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;


        if (words[middle].substr(0,prefix.size()) == prefix) { 
            return true; // Prefix found
        }

        // If the target is smaller, search the left half
        if (words[middle].substr(0,prefix.size()) > prefix) {
            right = middle - 1;
        }
        // If the target is larger, search the right half
        else {
            left = middle + 1;
        }
    }

    return false; // Word not found
}


class ScrabbleHelper {

private:
    vector<string> letters;
public:
    ScrabbleHelper() {}

    //TO DO: check if the user's input is valid through checking if the letters are in the alphabet as well as if the letters are in the right format


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

        void displayLetters(){
            cout << "Your letters are: ";
            for(int i = 0; i < letters.size(); i++){
                cout << letters[i] << " ";
            }
        }


};

int main() {
    ScrabbleHelper helper;
    helper.getLetters();
    helper.displayLetters();
    return 0;
}

