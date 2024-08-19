#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// assign points for letters
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

string lower(string word);
int score(string word);
int main(void)
{
    // take two inputs from user
    string i1 = get_string("Player 1: ");
    string i2 = get_string("Player 2: ");

    // change input to lower case
    i1 = lower(i1);
    i2 = lower(i2);

    // compute the scroes
    int sum1 = score(i1);
    int sum2 = score(i2);

    // print the winner
    if (sum1 > sum2)
    {
        printf("Player 1 wins!\n");
    }
    else if (sum2 > sum1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

string lower(string word)
{
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if(isupper(word[i]))
        {
            word[i] = tolower(word[i]);
        }
    }
    return word;
}
int score(string word)
{
    int index, sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if ((int) word[i] > 96 && (int) word[i] < 213)
        {
            index = (int) word[i] - 97;
            sum += points[index];
        }
    }
    return sum;
}
