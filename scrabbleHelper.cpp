#include "scrabbleHelper.h"

int main()
{
    ScrabbleHelper helper;

    helper.allValidWords();
    helper.displayWordsWithSuffix(helper.suffixSearch("ler"));
    return 0;
}


