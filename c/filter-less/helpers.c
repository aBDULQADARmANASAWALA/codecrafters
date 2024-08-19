#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int pixel;
    // loop through every pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the average of rgb
            pixel =
                round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);

            // assigning the pixel value to image
            image[i][j].rgbtRed = pixel;
            image[i][j].rgbtBlue = pixel;
            image[i][j].rgbtGreen = pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through every pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed, sepiaBlue, sepiaGreen;

            // calculating sepiaRed
            if (round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                      .189 * image[i][j].rgbtBlue) > 255)
            {
                sepiaRed = 255;
            }
            else
            {
                sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            }

            // calculating sepiaGreen
            if (round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                      .168 * image[i][j].rgbtBlue) > 255)
            {
                sepiaGreen = 255;
            }
            else
            {
                sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            }

            // calculating sepiaBlue
            if (round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                      .131 * image[i][j].rgbtBlue) > 255)
            {
                sepiaBlue = 255;
            }
            else
            {
                sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);
            }

            // assigining sepia values to image
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // loop throughevery pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swapping piels
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a copy of image array
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // topleft pixel
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) /
                          4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          4.0);
            }

            // topright pixel
            if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue) /
                          4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                          4.0);
            }

            // bottomleft pixel
            if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i - 1][j + 1].rgbtBlue) /
                          4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                          4.0);
            }

            // bottomright pixel
            if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                           copy[i - 1][j - 1].rgbtBlue) /
                          4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                          4.0);
            }

            // top row
            if (i == 0 && (j != 0 && j != width - 1))
            {
                image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) /
                          6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          6.0);
            }

            // bottom row
            if (i == height - 1 && (j != 0 && j != width - 1))
            {
                image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j + 1].rgbtBlue) /
                          6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                           copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                          6.0);
            }

            // left col
            if ((i != 0 && i != height - 1) && j == 0)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) /
                          6.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          6.0);
            }

            // right col
            if ((i != 0 && i != height - 1) && j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue) /
                          6.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                          6.0);
            }

            // rest of the pixels
            if ((i > 0 && j > 0) && (i < height - 1 && j < width - 1))
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i + 1][j + 1].rgbtRed) /
                                            9.0);
                image[i][j].rgbtBlue = round(
                    (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                     copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                     copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                     copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                    9.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i + 1][j + 1].rgbtGreen) /
                          9.0);
            }
        }
    }
    return;
}
