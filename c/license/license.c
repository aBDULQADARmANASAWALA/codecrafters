#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    /* **plates is a pointer to 8 other pointers that point to a char (or first bit of a string)

             plates
                |
                V
         plates[0] [1] [2] [3] [4] [5] [6] [7]
                |   |   |   |   |   |   |   |
                V   V   V   V   V   V   V   V
                s1  s2  s3  s4  s5  s6  s7  s8

       **plates stores address of the first bit of 8 other "pointers" which are contiguous in memory.
       Here every element of plates is a pointer, that is, plates[i] is the pointer (of size char*)
       which stores the address of the first character of a string.
    */

    // creating an array of strings of 8 elements
    int items = 8;
    int string_size = 6;

    char **plates = malloc(items * sizeof(char *));
    if (plates == NULL)
    {
        printf("Not enough memory.");
        return 1;
    }

    for (int i = 0; i < items; i++)
    {
        // extra +1 for \0 nul to declare end of a string
        plates[i] = malloc((string_size + 1) * sizeof(char));
        if (plates[i] == NULL)
        {
            printf("Not enough memory.");
            return 1;
        }
    }

    // storing address of input file
    FILE *infile = fopen(argv[1], "r");

    // Create buffer to read into
    char buffer[string_size + 1];

    int idx = 0;

    while (fread(buffer, 1, string_size + 1, infile))
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;
    }

    // printing the plate values
    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    // free up the memory
    for (int i = 0; i < 8; i++)
    {
        free(plates[i]);
    }
    free(plates);

    return 0;
}
