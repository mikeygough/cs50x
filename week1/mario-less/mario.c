#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt the user for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // loop through height
    for (int i = 0; i < height; i++)
    {
        // add spaces for right alignment
        for (int spaces = 1; spaces < height - i; spaces++)
        {
            printf(" ");
        }
        // add blocks
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}