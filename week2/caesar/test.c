#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

char rotate(char c, int n);

int main(void)
{
    char c = get_char("Char: \n");
    int k = get_int("Rotate Factor: \n");

    char new_char = rotate(c, k);
    printf("New Char: %c\n", new_char);
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