#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user for money owed
    int owe, remain, coin;
    do
    {
        owe = get_int("Change owed: ");
    }
    while (owe < 0);

    // check for 25
    coin = owe / 25;
    remain = owe % 25;

    // check for 10
    coin = coin + remain / 10;
    remain = remain % 10;

    // check for 5
    coin = coin + remain / 5;
    remain = remain % 5;

    // check for 1
    coin = coin + remain / 1;
    remain = remain % 1;

    // print amount of coins
    printf("%i \n", coin);
}
