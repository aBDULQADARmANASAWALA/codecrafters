#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // CHECKING FOR COMMAND LINE ARGUMENT
    // checking for a single command line arg
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    // checking for a 26 letter command line arg
    if (strlen(argv[1]) != 26)
    {
        printf("Key must be '26' letters.");
        return 1;
    }

    // checking all chacharacters for alphabets in command line arg
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must be 26 LETTERS.");
            return 1;
        }
    }

    // checking no duplicates in command line arg
    for (int i = 0, len = strlen(argv[1]); i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must be 26 UNIQUE letters.");
                return 1;
            }
        }
    }

    // taking user input
    string plaintext = get_string("plaintext: ");

    // CREATING CIPHERTEXT
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // for lower case
        if (islower(plaintext[i]))
        {
            plaintext[i] = tolower(argv[1][(int) plaintext[i] - 'a']);
        }

        // for upper case
        else if (isupper(plaintext[i]))
        {
            plaintext[i] = toupper(argv[1][(int) plaintext[i] - 'A']);
        }
    }

    // printing ciphertext
    printf("ciphertext: %s\n", plaintext);
    return 0;
}
