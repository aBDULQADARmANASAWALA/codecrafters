#include "helpers.h"
#include <math.h>
#include <stdlib.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    float rgx, rgy, bgx, bgy, ggx, ggy;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // topleft corner
            if (i == 0 && j == 0)
            {
                // for Red channel
                rgx = (float) abs(copy[i][j + 1].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1);
                rgy = (float) abs(copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1);

                // for Blue channel
                bgx = (float) abs(copy[i][j + 1].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue * 1);
                bgy = (float) abs(copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue * 1);

                // for Green channel
                ggx = (float) abs(copy[i][j + 1].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1);
                ggy = (float) abs(copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1);

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }

            // topright corner
            if (i == 0 && j == width - 1)
            {
                // for Red channel
                rgx =
                    (float) abs(copy[i][j - 1].rgbtRed * (-2) + copy[i + 1][j - 1].rgbtRed * (-1));
                rgy = (float) abs(copy[i + 1][j - 1].rgbtRed * 1 + copy[i + 1][j].rgbtRed * 2);

                // for Blue channel
                bgx = (float) abs(copy[i][j - 1].rgbtBlue * (-2) +
                                  copy[i + 1][j - 1].rgbtBlue * (-1));
                bgy = (float) abs(copy[i + 1][j - 1].rgbtBlue * 1 + copy[i + 1][j].rgbtBlue * 2);

                // for Green channel
                ggx = (float) abs(copy[i][j - 1].rgbtGreen * (-2) +
                                  copy[i + 1][j - 1].rgbtGreen * (-1));
                ggy = (float) abs(copy[i + 1][j - 1].rgbtGreen * 1 + copy[i + 1][j].rgbtGreen * 2);

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }

            // bottomleft corner
            if (i == height - 1 && j == 0)
            {
                // for Red channel
                rgx = (float) abs(copy[i - 1][j + 1].rgbtRed * 1 + copy[i][j + 1].rgbtRed * 2);
                rgy =
                    (float) abs(copy[i - 1][j].rgbtRed * (-2) + copy[i - 1][j + 1].rgbtRed * (-1));

                // for Blue channel
                bgx = (float) abs(copy[i - 1][j + 1].rgbtBlue * 1 + copy[i][j + 1].rgbtBlue * 2);
                bgy = (float) abs(copy[i - 1][j].rgbtBlue * (-2) +
                                  copy[i - 1][j + 1].rgbtBlue * (-1));

                // for Green channel
                ggx = (float) abs(copy[i - 1][j + 1].rgbtGreen * 1 + copy[i][j + 1].rgbtGreen * 2);
                ggy = (float) abs(copy[i - 1][j].rgbtGreen * (-2) +
                                  copy[i - 1][j + 1].rgbtGreen * (-1));

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }

            // bottomright corner
            if (i == height - 1 && j == width - 1)
            {
                // for Red channel
                rgx =
                    (float) abs(copy[i - 1][j - 1].rgbtRed * (-1) + copy[i][j - 1].rgbtRed * (-2));
                rgy =
                    (float) abs(copy[i - 1][j - 1].rgbtRed * (-1) + copy[i - 1][j].rgbtRed * (-2));

                // for Blue channel
                bgx = (float) abs(copy[i - 1][j - 1].rgbtBlue * (-1) +
                                  copy[i][j - 1].rgbtBlue * (-2));
                bgy = (float) abs(copy[i - 1][j - 1].rgbtBlue * (-1) +
                                  copy[i - 1][j].rgbtBlue * (-2));

                // for Green channel
                ggx = (float) abs(copy[i - 1][j - 1].rgbtGreen * (-1) +
                                  copy[i][j - 1].rgbtGreen * (-2));
                ggy = (float) abs(copy[i - 1][j - 1].rgbtGreen * (-1) +
                                  copy[i - 1][j].rgbtGreen * (-2));

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }

            // top row without corners
            if (i == 0 && (j != 0 && j != width - 1))
            {
                // for Red channel
                rgx =
                    (float) abs(copy[i][j - 1].rgbtRed * (-2) + copy[i + 1][j - 1].rgbtRed * (-1) +
                                copy[i][j + 1].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1);
                rgy = (float) abs(copy[i + 1][j - 1].rgbtRed * 1 + copy[i + 1][j].rgbtRed * 2 +
                                  copy[i + 1][j + 1].rgbtRed * 1);

                // for Blue channel
                bgx = (float) abs(copy[i][j - 1].rgbtBlue * (-2) +
                                  copy[i + 1][j - 1].rgbtBlue * (-1) + copy[i][j + 1].rgbtBlue * 2 +
                                  copy[i + 1][j + 1].rgbtBlue * 1);
                bgy = (float) abs(copy[i + 1][j - 1].rgbtBlue * 1 + copy[i + 1][j].rgbtBlue * 2 +
                                  copy[i + 1][j + 1].rgbtBlue * 1);

                // for Green channel
                ggx = (float) abs(copy[i][j - 1].rgbtGreen * (-2) +
                                  copy[i + 1][j - 1].rgbtGreen * (-1) +
                                  copy[i][j + 1].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1);
                ggy = (float) abs(copy[i + 1][j - 1].rgbtGreen * 1 + copy[i + 1][j].rgbtGreen * 2 +
                                  copy[i + 1][j + 1].rgbtGreen * 1);

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }

            // bottom row without corners
            if (i == height - 1 && (j != 0 && j != width - 1))
            {
                // for Red channel
                rgx =
                    (float) abs(copy[i - 1][j - 1].rgbtRed * (-1) + copy[i][j - 1].rgbtRed * (-2) +
                                copy[i - 1][j + 1].rgbtRed * 1 + copy[i][j + 1].rgbtRed * 2);
                rgy =
                    (float) abs(copy[i - 1][j - 1].rgbtRed * (-1) + copy[i - 1][j].rgbtRed * (-2) +
                                copy[i - 1][j + 1].rgbtRed * (-1));

                // for Blue channel
                bgx = (float) abs(copy[i - 1][j - 1].rgbtBlue * (-1) +
                                  copy[i][j - 1].rgbtBlue * (-2) + copy[i - 1][j + 1].rgbtBlue * 1 +
                                  copy[i][j + 1].rgbtBlue * 2);
                bgy = (float) abs(copy[i - 1][j - 1].rgbtBlue * (-1) +
                                  copy[i - 1][j].rgbtBlue * (-2) +
                                  copy[i - 1][j + 1].rgbtBlue * (-1));

                // for Green channel
                ggx = (float) abs(copy[i - 1][j - 1].rgbtGreen * (-1) +
                                  copy[i][j - 1].rgbtGreen * (-2) +
                                  copy[i - 1][j + 1].rgbtGreen * 1 + copy[i][j + 1].rgbtGreen * 2);
                ggy = (float) abs(copy[i - 1][j - 1].rgbtGreen * (-1) +
                                  copy[i - 1][j].rgbtGreen * (-2) +
                                  copy[i - 1][j + 1].rgbtGreen * (-1));

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }

            // left col without corners
            if ((i != 0 && i != height - 1) && j == 0)
            {
                // for Red channel
                rgx = (float) abs(copy[i - 1][j + 1].rgbtRed * 1 + copy[i][j + 1].rgbtRed * 2 +
                                  copy[i + 1][j + 1].rgbtRed * 1);
                rgy =
                    (float) abs(copy[i - 1][j].rgbtRed * (-2) + copy[i - 1][j + 1].rgbtRed * (-1) +
                                copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1);

                // for Blue channel
                bgx = (float) abs(copy[i - 1][j + 1].rgbtBlue * 1 + copy[i][j + 1].rgbtBlue * 2 +
                                  copy[i + 1][j + 1].rgbtBlue * 1);
                bgy = (float) abs(copy[i - 1][j].rgbtBlue * (-2) +
                                  copy[i - 1][j + 1].rgbtBlue * (-1) + copy[i + 1][j].rgbtBlue * 2 +
                                  copy[i + 1][j + 1].rgbtBlue * 1);

                // for Green channel
                ggx = (float) abs(copy[i - 1][j + 1].rgbtGreen * 1 + copy[i][j + 1].rgbtGreen * 2 +
                                  copy[i + 1][j + 1].rgbtGreen * 1);
                ggy = (float) abs(copy[i - 1][j].rgbtGreen * (-2) +
                                  copy[i - 1][j + 1].rgbtGreen * (-1) +
                                  copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1);

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }

            // right col without corners
            if ((i != 0 && i != height - 1) && j == width - 1)
            {
                // for Red channel
                rgx =
                    (float) abs(copy[i - 1][j - 1].rgbtRed * (-1) + copy[i][j - 1].rgbtRed * (-2) +
                                copy[i + 1][j - 1].rgbtRed * (-1));
                rgy =
                    (float) abs(copy[i - 1][j - 1].rgbtRed * (-1) + copy[i - 1][j].rgbtRed * (-2) +
                                copy[i + 1][j - 1].rgbtRed * 1 + copy[i + 1][j].rgbtRed * 2);

                // for Blue channel
                bgx = (float) abs(copy[i - 1][j - 1].rgbtBlue * (-1) +
                                  copy[i][j - 1].rgbtBlue * (-2) +
                                  copy[i + 1][j - 1].rgbtBlue * (-1));
                bgy = (float) abs(copy[i - 1][j - 1].rgbtBlue * (-1) +
                                  copy[i - 1][j].rgbtBlue * (-2) + copy[i + 1][j - 1].rgbtBlue * 1 +
                                  copy[i + 1][j].rgbtBlue * 2);

                // for Green channel
                ggx = (float) abs(copy[i - 1][j - 1].rgbtGreen * (-1) +
                                  copy[i][j - 1].rgbtGreen * (-2) +
                                  copy[i + 1][j - 1].rgbtGreen * (-1));
                ggy = (float) abs(copy[i - 1][j - 1].rgbtGreen * (-1) +
                                  copy[i - 1][j].rgbtGreen * (-2) +
                                  copy[i + 1][j - 1].rgbtGreen * 1 + copy[i + 1][j].rgbtGreen * 2);

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }

            // rest of the pixels
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                // for Red channel
                rgx =
                    (float) abs(copy[i - 1][j - 1].rgbtRed * (-1) + copy[i][j - 1].rgbtRed * (-2) +
                                copy[i + 1][j - 1].rgbtRed * (-1) + copy[i - 1][j + 1].rgbtRed * 1 +
                                copy[i][j + 1].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1);
                rgy =
                    (float) abs(copy[i - 1][j - 1].rgbtRed * (-1) + copy[i - 1][j].rgbtRed * (-2) +
                                copy[i - 1][j + 1].rgbtRed * (-1) + copy[i + 1][j - 1].rgbtRed * 1 +
                                copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1);

                // for Blue channel
                bgx = (float) abs(
                    copy[i - 1][j - 1].rgbtBlue * (-1) + copy[i][j - 1].rgbtBlue * (-2) +
                    copy[i + 1][j - 1].rgbtBlue * (-1) + copy[i - 1][j + 1].rgbtBlue * 1 +
                    copy[i][j + 1].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue * 1);
                bgy = (float) abs(
                    copy[i - 1][j - 1].rgbtBlue * (-1) + copy[i - 1][j].rgbtBlue * (-2) +
                    copy[i - 1][j + 1].rgbtBlue * (-1) + copy[i + 1][j - 1].rgbtBlue * 1 +
                    copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue * 1);

                // for Green channel
                ggx = (float) abs(
                    copy[i - 1][j - 1].rgbtGreen * (-1) + copy[i][j - 1].rgbtGreen * (-2) +
                    copy[i + 1][j - 1].rgbtGreen * (-1) + copy[i - 1][j + 1].rgbtGreen * 1 +
                    copy[i][j + 1].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1);
                ggy = (float) abs(
                    copy[i - 1][j - 1].rgbtGreen * (-1) + copy[i - 1][j].rgbtGreen * (-2) +
                    copy[i - 1][j + 1].rgbtGreen * (-1) + copy[i + 1][j - 1].rgbtGreen * 1 +
                    copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1);

                // updating new image
                image[i][j].rgbtRed = (int) round(
                    (sqrtf(rgx * rgx + rgy * rgy) > 255.0) ? 255.0 : sqrtf(rgx * rgx + rgy * rgy));
                image[i][j].rgbtBlue = (int) round(
                    (sqrtf(bgx * bgx + bgy * bgy) > 255.0) ? 255.0 : sqrtf(bgx * bgx + bgy * bgy));
                image[i][j].rgbtGreen = (int) round(
                    (sqrtf(ggx * ggx + ggy * ggy) > 255.0) ? 255.0 : sqrtf(ggx * ggx + ggy * ggy));
            }
        }
    }
    return;
}
