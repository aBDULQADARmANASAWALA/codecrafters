#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check if only one argument is in the input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check whether the input is alphabet
    int len = strlen(argv[1]);
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    //check whether the key has 26 letters
    if(len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string key = argv[1];
    //check if the key has all the letters unique
    for(int i = 0; i < len; i++)
    {
        key[i] = toupper(key[i]);
        for(int j = i + 1; j < len; j++)
        {
            if(toupper(key[i]) == toupper(key[j]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    //promt the user for plaintext
    string plain = get_string("plaintext: ");

    char cipher[strlen(plain) + 1];

    for(int i  = 0; i < strlen(plain); i++)
    {
        if(isupper(plain[i]))
        {
            cipher[i] = key[(plain[i] - 65)];
        }
        else if(islower(plain[i]))
        {
            plain[i] -= 32;
            cipher[i] = key[(plain[i] - 65)];
            cipher[i] += 32;
        }
        else if(!isalpha(plain[i]))
        {
            cipher[i] = plain[i];
        }
    }
    cipher[strlen(plain)] = '\0';

    printf("ciphertext: %s\n", cipher);
}
