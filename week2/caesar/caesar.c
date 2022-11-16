#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int n);
bool only_digits(string s);

int main(int argc, string argv[])
{
    // check number of command line arguments
    if ((argc < 2) || (argc > 2))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // check that argv[1] is a digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // convert argv[1] from a 'string' to an 'int'
    int k = atoi(argv[1]);

    // prompt user for plaintext
    string p = get_string("plaintext:  ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(p); i++)
    {
        printf("%c", rotate(p[i], k));
    }
    printf("\n");

    return 0;

}

// function that rotates char
char rotate(char c, int n)
{
    if (!isalpha(c))
    {
        return c;
    }
    else
    {
        if (isupper(c))
        {
            return (((c - 65) + n) % 26) + 65;
        }
        else if (islower(c))
        {
            return (((c - 97) + n) % 26) + 97;
        }
        else
        {
            return 1;
        }
    }
}

// function that checks whether or not the key is a digit
bool only_digits(string s)
{
    int counter = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]))
        {
            counter += 0;
        }
        else
        {
            counter += 1;
        }
    }
    if (counter == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

