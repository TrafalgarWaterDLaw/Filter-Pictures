#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
   for ( int i = 0; i < height; i++)
   {
       for (int j = 0; j < width; j++)
       {
            RGBTRIPLE pixel = image[i][j];
            float averagePixel = (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.00;
            int avg = round(averagePixel);

            //Applying Grey filter
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;

       }
   }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for ( int i = 0; i < height; i++)
    {
       for (int j = 0; j < width; j++)
       {
            //formula to calculate sepia
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //Check weather result of round is greater than 255
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;

       }
    }
    return;

}

//Swapping values/ pointers
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for ( int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
       {
           swap(&image[i][j], &image[i][width -1 - j]);
       }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy of the image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0;
            int sumRed = 0;
            int sumGreen = 0;
            float counter = 0.00;

            for ( int k = -1; k < 2; k++)
            {
                for ( int h = -1; h < 2; h++)
                {
                    if ( i + k < 0 || i + k > height - 1 || j + h < 0 || j + h > width -1)
                    {
                        continue;
                    }

                    sumBlue += image[i + k][j + h].rgbtBlue;
                    sumRed += image[i + k][j + h].rgbtRed;
                    sumGreen += image[i + k][j + h].rgbtGreen;

                    counter++;
                }
            }

            copy[i][j].rgbtBlue = round(sumBlue/counter);
            copy[i][j].rgbtRed = round(sumRed/counter);
            copy[i][j].rgbtGreen = round(sumGreen/counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }

    return;
}
