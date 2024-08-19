#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

int main(int argc, char *argv[])
{
    // checking for number of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover file_name\n");
        return 1;
    }

    // opening the given file
    // file stores the address of given file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Given file cannot be opened");
        return 1;
    }

    // creating a buffer array to store file contents
    uint8_t buffer[BLOCK];

    // defining a string to store the formatted name of new img file
    // (###.jpg)
    char *output = malloc(8);

    // a variable to store number of header files found
    // or number of new JPEGs / JPGs
    int counter = 0;

    // img will store the address of new JPEG / JPG file
    FILE *img;

    // reading through the file
    while (fread(&buffer, sizeof(uint8_t), BLOCK, file))
    {
        /*
            for buffer[3], we are using bitwise AND operator
            it results in AND operation of two operands for every single bit
            if one operand is 'f' aka 1111, then it always results in the other operand
            if one operand is '0' aka 0000, then it always results 0 for every single bit
        */

        // if no JPEG / JPG header found, then writing the contents of file
        // to the already open img file
        if (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
              (buffer[3] & 0xf0) == 0xe0) &&
            counter != 0)
        {
            fwrite(&buffer, sizeof(uint8_t), 512, img);
        }

        // checking for jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // closing the previously opened img file (if any)
            if (counter != 0)
            {
                fclose(img);
            }

            // creating 'formatted string' name for new img file
            sprintf(output, "%03i.jpg", counter);
            counter++;

            // assigning the address of new JPEG / JPG file to img
            img = fopen(output, "w");

            // writing the contents of file to img
            fwrite(&buffer, sizeof(uint8_t), 512, img);
        }
    }

    // freeing memory and closing all open files
    free(output);
    fclose(img);
    fclose(file);
    return 0;
}
