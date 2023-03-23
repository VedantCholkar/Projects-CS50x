#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0); // Finds the average of RGB
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (red > 255) // Sets a max
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // Repeat height times
    {
        for (int j = 0, k = ceil(width / 2); j < k; j++) // Repeat width / 2
        {
            RGBTRIPLE tmp;
            int last_pixel = 0;
            tmp = image[i][j];
            last_pixel = width - j - 1;
            image[i][j] = image[i][last_pixel];
            image[i][last_pixel] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = 0, g = 0, b = 0, count = 0;

            for (int k = -1; k <= 1; k++) // Checks to surrounding pixels
            {
                for (int l = -1; l <= 1; l++)
                {
                    int row = i + k;
                    int column = j + l;

                    if (row >= 0 && row < height && column >= 0 && column < width) // Checks if current pixel is valid
                    {
                        r += image[row][column].rgbtRed;
                        g += image[row][column].rgbtGreen;
                        b += image[row][column].rgbtBlue;
                        count++;
                    }
                }
            }

            copy[i][j].rgbtRed = round((float)r / count);
            copy[i][j].rgbtGreen = round((float)g / count);
            copy[i][j].rgbtBlue = round((float)b / count);
        }
    }

    for (int i = 0; i < height; i++) // Copies the blurred image to original image
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
