#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);
int len;
int num = 0;
int index = 0;

int main(void)
{
    string input = get_string("Enter a positive integer: ");
    len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    if (index == strlen(input))
    {
        return num;
    }
    num = num * 10 + (input[index] - '0');
    index++;
    convert(input);
    return num;
}
