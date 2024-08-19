#include <stdio.h>
#include <cs50.h>
#include <string.h>

long letters(string s);
int main(void)
{
    string str = get_string("Type: ");
    printf("%li\n", letters(str));
}

long letters(string s)
{
    long and = strlen(s);
    for (int j = 0; j < and; j++)
    {
        if (s[j] == ' ' || s[j] == '.' || s[j] == '!' || s[j] == '?')
        {
            and--;
        }
    }
    return and;
}
