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
            float average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.00);

            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // The sepia color is going to be...formula
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);

            // But if somehow it gets greater than 255 than it's gonna be 255 (cuz it's the highest possible)
            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;

            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width/2); j++)
        {
            RGBTRIPLE temp = image[i][j]; // The current pixel is stored in a temporary variable
            image[i][j] = image[i][width - 1 - j]; // The current pixel gets the value of your equivalent position from right to left
            image[i][width - 1 - j] = temp;  // And the reverse happens
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float sum_red = 0, sum_blue = 0, sum_green = 0;
    RGBTRIPLE temp[height][width];
    float countPix = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            countPix = 0;
            sum_red = 0;
            sum_green = 0;
            sum_blue = 0;
            
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        countPix++;
                        sum_red += image[k][l].rgbtRed;
                        sum_green += image[k][l].rgbtGreen;
                        sum_blue += image[k][l].rgbtBlue;
                    }
                }    
            }
            
            temp[i][j].rgbtRed = (int) round(sum_red/countPix);
            temp[i][j].rgbtGreen = (int) round(sum_green/countPix);
            temp[i][j].rgbtBlue = (int) round(sum_blue/countPix);
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
}
