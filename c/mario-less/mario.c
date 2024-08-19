#include <cs50.h>
#include <stdio.h>

void print_row(int height, int bricks);

int main(void)
{
    // get the height from the user
    int h;
    do
    {
        h = get_int("Enter the height:\n");
    }
    while (h < 1);

    // print bricks
    for (int i = 0; i < h; i++)
    {
        // print rows of bricks
        print_row(h, i + 1);
    }
}

void print_row(int height, int bricks)
{
    // print spaces
    int space = height - bricks;
    for (int i = 0; i < space; i++)
    {
        printf(" ");
    }
    // print #
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    // print next line
    printf("\n");
}
