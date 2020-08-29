#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int stop;
    int total = width - 1;
    if (width % 2 == 0)
    {
        stop = (width / 2) - 1;
    }
    else
    {
        stop = (width / 2) - 0.5;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= stop; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][total - j];
            image[i][total - j] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                int avRED = round((image_copy[i][j + 1].rgbtRed + image_copy[i][j].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i + 1][j +
                1].rgbtRed) / 4.0);
                int avGREEN = round((image_copy[i][j + 1].rgbtGreen + image_copy[i][j].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i +
                1][j + 1].rgbtGreen) / 4.0);
                int avBLUE = round((image_copy[i][j + 1].rgbtBlue + image_copy[i][j].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i +
                1][j + 1].rgbtBlue) / 4.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
            else if (i == 0 && j == width - 1)
            {
                int avRED = round((image_copy[i][j - 1].rgbtRed + image_copy[i][j].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i + 1][j -
                1].rgbtRed) / 4.0);
                int avGREEN = round((image_copy[i][j - 1].rgbtGreen + image_copy[i][j].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i +
                1][j - 1].rgbtGreen) / 4.0);
                int avBLUE = round((image_copy[i][j - 1].rgbtBlue + image_copy[i][j].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i + 1][j
                - 1].rgbtBlue) / 4.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
            else if (i == height - 1 && j == 0)
            {
                int avRED = round((image_copy[i][j + 1].rgbtRed + image_copy[i][j].rgbtRed +image_copy[i - 1][j].rgbtRed + image_copy[i - 1][j +
                1].rgbtRed) / 4.0);
                int avGREEN = round((image_copy[i][j + 1].rgbtGreen + image_copy[i][j].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i -
                1][j + 1].rgbtGreen) / 4.0);
                int avBLUE = round((image_copy[i][j + 1].rgbtBlue + image_copy[i][j].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i - 1][j
                + 1].rgbtBlue) / 4.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
            else if (i == height - 1 && j == width - 1)
            {
                int avRED = round((image_copy[i][j - 1].rgbtRed + image_copy[i][j].rgbtRed + image_copy[i - 1][j].rgbtRed + image_copy[i - 1][j -
                1].rgbtRed) / 4.0);
                int avGREEN = round((image_copy[i][j - 1].rgbtGreen + image_copy[i][j].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i -
                1][j - 1].rgbtGreen) / 4.0);
                int avBLUE = round((image_copy[i][j - 1].rgbtBlue + image_copy[i][j].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i - 1][j
                - 1].rgbtBlue) / 4.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
            else if (i == 0 && j > 0 && j < width - 1)
            {
                int avRED = round((image_copy[i][j - 1].rgbtRed + image_copy[i][j].rgbtRed + image_copy[i][j + 1].rgbtRed + image_copy[i + 1][j -
                1].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i + 1][j + 1].rgbtRed) / 6.0);
                int avGREEN = round((image_copy[i][j - 1].rgbtGreen + image_copy[i][j].rgbtGreen + image_copy[i][j + 1].rgbtGreen + image_copy[i +
                1][j - 1].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i + 1][j + 1].rgbtGreen) / 6.0);
                int avBLUE = round((image_copy[i][j - 1].rgbtBlue + image_copy[i][j].rgbtBlue + image_copy[i][j + 1].rgbtBlue + image_copy[i + 1][j
                - 1].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i + 1][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                int avRED = round((image_copy[i][j - 1].rgbtRed + image_copy[i][j].rgbtRed + image_copy[i][j + 1].rgbtRed + image_copy[i - 1][j -
                1].rgbtRed + image_copy[i - 1][j].rgbtRed + image_copy[i - 1][j + 1].rgbtRed) / 6.0);
                int avGREEN = round((image_copy[i][j - 1].rgbtGreen + image_copy[i][j].rgbtGreen + image_copy[i][j + 1].rgbtGreen + image_copy[i -
                1][j - 1].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i - 1][j + 1].rgbtGreen) / 6.0);
                int avBLUE = round((image_copy[i][j - 1].rgbtBlue + image_copy[i][j].rgbtBlue + image_copy[i][j + 1].rgbtBlue + image_copy[i - 1][j
                - 1].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i - 1][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
            else if (j == 0 && i > 0 && i < height - 1)
            {
                int avRED = round((image_copy[i - 1][j].rgbtRed + image_copy[i - 1][j + 1].rgbtRed + image_copy[i][j + 1].rgbtRed +
                image_copy[i][j].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i + 1][j + 1].rgbtRed) / 6.0);
                int avGREEN = round((image_copy[i - 1][j].rgbtGreen + image_copy[i - 1][j + 1].rgbtGreen + image_copy[i][j + 1].rgbtGreen +
                image_copy[i][j].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i + 1][j + 1].rgbtGreen) / 6.0);
                int avBLUE = round((image_copy[i - 1][j].rgbtBlue + image_copy[i - 1][j + 1].rgbtBlue + image_copy[i][j + 1].rgbtBlue +
                image_copy[i][j].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i + 1][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
            else if (j == width - 1 && i > 0 && i < height - 1)
            {
                int avRED = round((image_copy[i - 1][j - 1].rgbtRed + image_copy[i - 1][j].rgbtRed + image_copy[i][j - 1].rgbtRed +
                image_copy[i][j].rgbtRed + image_copy[i + 1][j - 1].rgbtRed + image_copy[i + 1][j].rgbtRed) / 6.0);
                int avGREEN = round((image_copy[i - 1][j - 1].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i][j - 1].rgbtGreen +
                image_copy[i][j].rgbtGreen + image_copy[i + 1][j - 1].rgbtGreen + image_copy[i + 1][j].rgbtGreen) / 6.0);
                int avBLUE = round((image_copy[i - 1][j - 1].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i][j - 1].rgbtBlue +
                image_copy[i][j].rgbtBlue + image_copy[i + 1][j - 1].rgbtBlue + image_copy[i + 1][j].rgbtBlue) / 6.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
            else
            {
                int avRED = round((image_copy[i - 1][j - 1].rgbtRed + image_copy[i - 1][j].rgbtRed + image_copy[i - 1][j + 1].rgbtRed +
                image_copy[i][j - 1].rgbtRed + image_copy[i][j].rgbtRed + image_copy[i][j + 1].rgbtRed + image_copy[i + 1][j - 1].rgbtRed +
                image_copy[i + 1][j].rgbtRed + image_copy[i + 1][j + 1].rgbtRed) / 9.0);
                int avBLUE = round((image_copy[i - 1][j - 1].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i - 1][j + 1].rgbtBlue +
                image_copy[i][j - 1].rgbtBlue + image_copy[i][j].rgbtBlue + image_copy[i][j + 1].rgbtBlue + image_copy[i + 1][j - 1].rgbtBlue +
                image_copy[i + 1][j].rgbtBlue + image_copy[i + 1][j + 1].rgbtBlue) / 9.0);
                int avGREEN = round((image_copy[i - 1][j - 1].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i - 1][j + 1].rgbtGreen +
                image_copy[i][j - 1].rgbtGreen + image_copy[i][j].rgbtGreen + image_copy[i][j + 1].rgbtGreen + image_copy[i + 1][j - 1].rgbtGreen +
                image_copy[i + 1][j].rgbtGreen + image_copy[i + 1][j + 1].rgbtGreen) / 9.0);

                image[i][j].rgbtRed = avRED;
                image[i][j].rgbtGreen = avGREEN;
                image[i][j].rgbtBlue = avBLUE;
            }
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int redav;
    int blueav;
    int greenav;

    RGBTRIPLE image_copy[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1)
            {
                image_copy[i][j].rgbtRed = 0;
                image_copy[i][j].rgbtGreen = 0;
                image_copy[i][j].rgbtBlue = 0;
            }
            else if (j == 0 || j == width + 1)
            {
                image_copy[i][j].rgbtRed = 0;
                image_copy[i][j].rgbtGreen = 0;
                image_copy[i][j].rgbtBlue = 0;
            }
            else
            {
                image_copy[i][j] = image[i - 1][j - 1];
            }
        }
    }

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i > 0 && i < height + 1 && j > 0 && j < width + 1)
            {
                int redx = -1 * image_copy[i - 1][j - 1].rgbtRed + 0 * image_copy[i - 1][j].rgbtRed + 1 * image_copy[i - 1][j + 1].rgbtRed + -2 *
                image_copy[i][j - 1].rgbtRed + 0 * image_copy[i][j].rgbtRed + 2 * image_copy[i][j + 1].rgbtRed + -1 * image_copy[i + 1][j -
                1].rgbtRed + 0 * image_copy[i + 1][j].rgbtRed + 1 * image_copy[i + 1][j + 1].rgbtRed;
                int redy = -1 * image_copy[i - 1][j - 1].rgbtRed + -2 * image_copy[i - 1][j].rgbtRed + -1 * image_copy[i - 1][j + 1].rgbtRed + 0 *
                image_copy[i][j - 1].rgbtRed + 0 * image_copy[i][j].rgbtRed + 0 * image_copy[i][j + 1].rgbtRed + 1 * image_copy[i + 1][j -
                1].rgbtRed + 2 * image_copy[i + 1][j].rgbtRed + 1 * image_copy[i + 1][j + 1].rgbtRed;

                int bluex = -1 * image_copy[i - 1][j - 1].rgbtBlue + 0 * image_copy[i - 1][j].rgbtBlue + 1 * image_copy[i - 1][j + 1].rgbtBlue + -2
                * image_copy[i][j - 1].rgbtBlue + 0 * image_copy[i][j].rgbtBlue + 2 * image_copy[i][j + 1].rgbtBlue + -1 * image_copy[i + 1][j -
                1].rgbtBlue + 0 * image_copy[i + 1][j].rgbtBlue + 1 * image_copy[i + 1][j + 1].rgbtBlue;
                int bluey = -1 * image_copy[i - 1][j - 1].rgbtBlue + -2 * image_copy[i - 1][j].rgbtBlue + -1 * image_copy[i - 1][j + 1].rgbtBlue + 0
                * image_copy[i][j - 1].rgbtBlue + 0 * image_copy[i][j].rgbtBlue + 0 * image_copy[i][j + 1].rgbtBlue + 1 * image_copy[i + 1][j -
                1].rgbtBlue + 2 * image_copy[i + 1][j].rgbtBlue + 1 * image_copy[i + 1][j + 1].rgbtBlue;

                int greenx = -1 * image_copy[i - 1][j - 1].rgbtGreen + 0 * image_copy[i - 1][j].rgbtGreen + 1 * image_copy[i - 1][j + 1].rgbtGreen +
                -2 * image_copy[i][j - 1].rgbtGreen + 0 * image_copy[i][j].rgbtGreen + 2 * image_copy[i][j + 1].rgbtGreen + -1 * image_copy[i + 1][j
                - 1].rgbtGreen + 0 * image_copy[i + 1][j].rgbtGreen + 1 * image_copy[i + 1][j + 1].rgbtGreen;
                int greeny = -1 * image_copy[i - 1][j - 1].rgbtGreen + -2 * image_copy[i - 1][j].rgbtGreen + -1 * image_copy[i - 1][j + 1].rgbtGreen
                + 0 * image_copy[i][j - 1].rgbtGreen + 0 * image_copy[i][j].rgbtGreen + 0 * image_copy[i][j + 1].rgbtGreen + 1 * image_copy[i + 1][j
                - 1].rgbtGreen + 2 * image_copy[i + 1][j].rgbtGreen + 1 * image_copy[i + 1][j + 1].rgbtGreen;


                redav = round(sqrt(pow(redx, 2) + pow(redy, 2)));
                blueav = round(sqrt(pow(bluex, 2) + pow(bluey, 2)));
                greenav = round(sqrt(pow(greenx, 2) + pow(greeny, 2)));

                if (redav > 255)
                {
                    redav = 255;
                }
                if (blueav > 255)
                {
                    blueav = 255;
                }
                if (greenav > 255)
                {
                    greenav = 255;
                }

                image[i - 1][j - 1].rgbtRed = redav;
                image[i - 1][j - 1].rgbtBlue = blueav;
                image[i - 1][j - 1].rgbtGreen = greenav;
            }
            else
            {
                continue;
            }
        }
    }
}
