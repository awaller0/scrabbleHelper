#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    std::ifstream file("scrabble_words.txt");
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::vector<std::string> words;
    std::string word;

    // Read words into the vector
    while (file >> word) {
        words.push_back(word);
    }

    file.close();
    return 0;
}
