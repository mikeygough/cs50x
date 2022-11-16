// before going on vacation i changed some of the variables to double from int.
// i need to formally apply this change i think it's working now!
// could probably actually just cast these as floats as well and be fine!

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

// coleman-liau index = 0.0588 * L - 0.296 * S - 15.8
// L is the average number of letters per 100 words in the text
// S is the average number of sentences per 100 words in the text

int main(void)
{
    string text;
    text = get_string("Text: ");

    // calculate number of letters
    int length_text = count_letters(text);
    // printf("%i letters\n", length_text);

    // calculate number of words
    int length_words = count_words(text);
    // printf("%i words\n", length_words);

    // calculate number of sentences
    int length_sentences = count_sentences(text);
    // printf("%i sentences\n", length_sentences);

    // compute coleman-lau index
    int coleman_liau_index;
    float L;
    float S;

    L = (((float)length_text / length_words) * 100.);
    S = (((float)length_sentences / length_words) * 100.);

    // printf("L = %f\n", L);
    // printf("S = %f\n", S);

    coleman_liau_index = (int) round(0.0588 * L - 0.296 * S - 15.8);

    if (coleman_liau_index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman_liau_index == 2)
    {
        printf("Grade 2\n");
    }
    else if (coleman_liau_index == 3)
    {
        printf("Grade 3\n");
    }
    else if (coleman_liau_index == 4)
    {
        printf("Grade 4\n");
    }
    else if (coleman_liau_index == 5)
    {
        printf("Grade 5\n");
    }
    else if (coleman_liau_index == 6)
    {
        printf("Grade 6\n");
    }
    else if (coleman_liau_index == 7)
    {
        printf("Grade 7\n");
    }
    else if (coleman_liau_index == 8)
    {
        printf("Grade 8\n");
    }
    else if (coleman_liau_index == 9)
    {
        printf("Grade 9\n");
    }
    else if (coleman_liau_index == 10)
    {
        printf("Grade 10\n");
    }
    else if (coleman_liau_index == 11)
    {
        printf("Grade 11\n");
    }
    else if (coleman_liau_index == 12)
    {
        printf("Grade 12\n");
    }
    else if (coleman_liau_index == 13)
    {
        printf("Grade 13\n");
    }
    else if (coleman_liau_index == 14)
    {
        printf("Grade 14\n");
    }
    else if (coleman_liau_index == 15)
    {
        printf("Grade 15\n");
    }
    else if (coleman_liau_index >= 16)
    {
        printf("Grade 16+\n");
    }

    // printf("Coleman Liau Index: %i\n", coleman_liau_index);
}

int count_letters(string text) // return the number of alphabetical characters in a string
{
    int length = 0; // initialize length
    for (int i = 0; i < strlen(text); i++) // loop through the chars in text
    {
        // check for alphabetical characters
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            length += 1; // update the length by 1
        }
        else
        {
            length += 0; // update the length by 0, not an alphabetical character
        }
    }
    return length; // return the length
}

int count_words(string text) // return the number of words (separated by a space) in a string
{
    int length = 0; // initialize length
    for (int i = 0; i < strlen(text); i++) // loop through the chars in text
    {
        // check for spaces
        if (text[i] == 32)
        {
            length += 1;
        }
        else
        {
            length += 0;
        }
    }
    return length + 1;
}

int count_sentences(string text) // return the number of sentences (occurence of . ! ?)
{
    int length = 0; // initialize length
    for (int i = 0; i < strlen(text); i++) // loop through the chars in text
    {
        if ((text[i] == 33) || (text[i] == 46) || (text[i] == 63))
        {
            length += 1; // update the length by 1
        }
        else
        {
            length += 0; // update the length by 0, not a sentence ending character
        }
    }
    return length; // return the length
}