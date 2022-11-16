#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");

    // for loop example
    for (int i = 0; i < strlen(word1); i++)
    {
        printf("%c\n", word1[i]);
    }

}

