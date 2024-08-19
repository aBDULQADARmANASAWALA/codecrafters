#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // single arg for main fn
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // digit only arg for main fn
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // defining key and changing string to int
    int key = atoi(argv[1]);

    // asking for input
    string plaintext = get_string("plaintext:  ");

    // making ciphertext
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // for lower case
        if (islower(plaintext[i]))
        {
            plaintext[i] -= 'a';
            plaintext[i] = ((int) plaintext[i] + key) % 26;
            plaintext[i] += 'a';
        }

        // for upper case
        else if (isupper(plaintext[i]))
        {
            plaintext[i] -= 'A';
            plaintext[i] = ((int) plaintext[i] + key) % 26;
            plaintext[i] += 'A';
        }
    }

    // printing ciphertext
    printf("ciphertext: %s\n", plaintext);

    return 0;
}
