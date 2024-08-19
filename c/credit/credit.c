#include <cs50.h>
#include <stdio.h>

long cardno;
int sum;

int checksum(long cardno);
int card_len(long cardno);
int main(void)
{
    // take card input from user
    cardno = get_long("Number: ");
    int len = card_len(cardno);

    sum = checksum(cardno);

    // checking card name
    if (sum % 10 == 0)
    {
        // for 15 digit
        // querying first digit
        int check = cardno / 10000000000000;

        // for 16 digit
        // querying first digit of cardno
        int check1 = cardno / 1000000000000000;
        // querying first two digits of cardno
        int check2 = cardno / 100000000000000;

        // for 13 digit
        if (len == 13 && cardno / 1000000000000 == 4)
        {
            printf("VISA\n");
        }

        // for 15 digit
        else if (len == 15 && (check == 34 || check == 37))
        {
            printf("AMEX\n");
        }

        // for 16 digit
        else if (len == 16 && check1 == 4)
        {
            printf("VISA\n");
        }
        else if (len == 16 && (check2 >= 51 && check2 <= 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int card_len(long n)
{
    int len = 1;
    while (n > 9)
    {
        len++;
        n /= 10;
    }
    return len;
}

int checksum(long card)
{
    long total = 0;

    // digits at even places
    for (long i = 10; i < 100000000000000000; i = i * 100)
    {
        long n = card % (i * 10);
        n = n / i;
        n = n * 2;
        if (n > 9)
        {
            n = (n % 10) + 1;
        }
        total += n;
    }

    // digits at odd places
    for (long i = 1; i < 10000000000000000; i = i * 100)
    {
        long n = card % (i * 10);
        n = n / i;
        total += n;
    }

    return (int) total;
}
