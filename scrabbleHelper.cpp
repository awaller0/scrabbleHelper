#include "scrabbleHelper.h"

int main()
{
    ScrabbleHelper helper;
    helper.readLettersFromUser();
    helper.displayPossibleWords("","");
    return 0;
}