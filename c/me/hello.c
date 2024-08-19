#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // gets input from the user
    string name = get_string("What is your name?\n");
    // prints the name of the user
    printf("Hello, %s\n", name);
}
