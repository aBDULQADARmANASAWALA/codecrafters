// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort(avg_temp array[], int size);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort(temps, NUM_CITIES);

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort(avg_temp array[], int size)
{
    /*
    // bubble sort
    avg_temp temp;
    bool swapped = true;

    while(true)
    {
        swapped = false;
        for (int i = 0; i < NUM_CITIES; i++)
        {
            if (temps[i].temp < temps[i + 1].temp)
            {
                temp = temps[i];
                temps[i] = temps[i + 1];
                temps[i + 1] = temp;

                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
    */

    // merge sort
    if (size == 1)
    {
        return;
    }

    avg_temp half1[size / 2];
    for (int i = 0; i < size / 2; i++)
    {
        half1[i] = array[i];
    }

    avg_temp half2[size - size / 2];
    for (int i = 0; i < size - size / 2; i++)
    {
        half2[i] = array[size / 2 + i];
    }

    sort(half1, size / 2);
    sort(half2, size - size / 2);

    int index = 0, i = 0, j = 0;
    int last;
    /*
    for (int i = 0; i < size / 2; i++)
    {
        for (int j = 0; j < size - size / 2; j++)
        {
            if (half1[i].temp > half2[j].temp)
            {
                array[index] = half1[i];
                index++;
                last = 1;
            }
            else if (half1[i].temp < half2[j].temp)
            {
                array[index] = half2[j];
                index++;
                last = 2;
            }
        }
    }
    */
    while(i < size / 2 && j < size - size / 2)
    {
        if (half1[i].temp > half2[j].temp)
        {
            array[index] = half1[i];
            index++;
            i++;
            last = 1;
        }
        else if (half1[i].temp < half2[j].temp)
        {
            array[index] = half2[j];
            index++;
            j++;
            last = 2;
        }
        else if (half1[i].temp == half2[j].temp)
        {
            array[index] = half1[i];
            index++;
            i++;
            array[index] = half2[j];
            index++;
            j++;
            last = 0;
        }
    }

    if (last == 1)
    {
        array[index] = half2[size - size / 2 - 1];
    }
    else if (last == 2)
    {
        array[index] = half1[size / 2 - 1];
    }
    return;
}
