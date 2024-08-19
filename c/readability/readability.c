#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // ask for input
    string text = get_string("Text: ");
    int len = strlen(text);

    // count total letters
    float letter = 0.0;
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letter++;
        }
    }

    // count total words
    float word = 1.0;
    for (int i = 0; i < len; i++)
    {
        if (isspace(text[i]))
        {
            word++;
        }
    }

    // count total sentences
    float sent = 0.0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sent++;
        }
    }

    // calc grade
    float L = letter / word * 100.0;
    float S = sent / word * 100.0;
    float formula = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(formula);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
