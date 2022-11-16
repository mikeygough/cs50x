#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check number of command line arguments
    // must be 2
    if ((argc < 2) || (argc > 2))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check key is 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // check key contains all alphabetical characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetical characters\n");
            return 1;
        }
    }

    // check key contains each character exactly once (case insensitive)
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        // store which character to count
        char c = argv[1][i];
        // initialize the count to 0
        int char_count = 0;

        // loop through the string and count the number of times that char appears
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (argv[1][j] == c)
            {
                char_count += 1;
            }
        }
        // if the character appears more than once exit and display the error message
        if (char_count > 1)
        {
            printf("Key must not contain repeated characters\n");
            return 1;
        }
    }

    // prompt user for plaintext
    string p = get_string("plaintext:  ");

    // ENCIPHER
    // 1. Find which letter of the alphabet the ith character of plaintext is...
    printf("ciphertext: ");
    for (int i = 0; i < strlen(p); i++)
    {
        int char_pos;

        // filter for alphabetical

        if (isalpha(p[i]))
        {

            if (isupper(p[i]))
            {
                char_pos = p[i] - 65; // get the alphabetical position for slicing through key (UPPERCASE)
                printf("%c", toupper(argv[1][char_pos]));
            }
            else if (islower(p[i]))
            {
                char_pos = p[i] - 97; // get the alphabetical position for slicing through key (LOWERCASE)
                printf("%c", tolower(argv[1][char_pos]));
            }
            else
            {
                char_pos = 0;
            }
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
    return 0;
}