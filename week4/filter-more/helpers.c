#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // calculate the average of the red, green, and blue values
    // set each rgb value to that average (and be sure to round)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (int) round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half_width = (int) round(width / 2);
    for (int i = 0; i < height; i++)
    {
        int j = 0;
        while (j < half_width)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
            j += 1;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // loop through image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize conditional logic
            int ignore_top_row = 0;
            int ignore_bottom_row = 0;
            int ignore_left_column = 0;
            int ignore_right_column = 0;

            if ((i - 1) < 0)
            {
                ignore_top_row += 1;
            }
            if ((i + 1) == height)
            {
                ignore_bottom_row += 1;
            }
            if ((j - 1) < 0)
            {
                ignore_left_column += 1;
            }
            if ((j + 1) == width)
            {
                ignore_right_column += 1;
            }

            if (ignore_top_row == 1 && ignore_left_column == 1) // Top Left
            {
                // printf("i = %i, j = %i - Top Left Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) /
                                              4.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j +
                                                 1].rgbtGreen) / 4.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j +
                                                1].rgbtBlue) / 4.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;

            }
            else if (ignore_top_row == 1 && ignore_right_column == 1) // Top Right
            {
                // printf("i = %i, j = %i - Top Right Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                                              4.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i +
                                                 1][j].rgbtGreen) / 4.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i +
                                                1][j].rgbtBlue) / 4.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;
            }
            else if (ignore_left_column == 1 && ignore_bottom_row == 1) // Bottom Left
            {
                // printf("i = %i, j = %i - Bottom Left Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) /
                                              4.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j +
                                                 1].rgbtGreen) / 4.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j +
                                                1].rgbtBlue) / 4.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;
            }
            else if (ignore_right_column == 1 && ignore_bottom_row == 1) // Bottom Right
            {
                // printf("i = %i, j = %i - Bottom Right Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed) /
                                              4.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i -
                                                 1][j].rgbtGreen) / 4.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i -
                                                1][j].rgbtBlue) / 4.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;
            }
            else if (ignore_top_row == 1 && ignore_left_column == 0 && ignore_right_column == 0) // Top (not corner)
            {
                // printf("i = %i, j = %i - Top (not corner) Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                               copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j -
                                                 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j -
                                                1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;
            }
            else if (ignore_left_column == 1 && ignore_top_row == 0 && ignore_bottom_row == 0) // Left (not corner)
            {
                // printf("i = %i, j = %i - Left (not corner) Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                               copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j +
                                                 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j +
                                                1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;
            }
            else if (ignore_right_column == 1 && ignore_top_row == 0 && ignore_bottom_row == 0) // Right (not corner)
            {
                // printf("i = %i, j = %i - Right (not corner) Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                               copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 6.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j -
                                                 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 6.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j -
                                                1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 6.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;
            }
            else if (ignore_bottom_row == 1 && ignore_left_column == 0 && ignore_right_column == 0) // Bottom (not corner)
            {
                // printf("i = %i, j = %i - Bottom (not corner) Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                                               + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed) / 6.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j +
                                                 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 6.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j +
                                                1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 6.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;
            }
            else
            {
                // printf("i = %i, j = %i - Center Pixel\n", i, j);
                int avg_rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                                               + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j +
                                                       1].rgbtRed) / 9.);
                int avg_rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j +
                                                 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                                 copy[i + 1][j + 1].rgbtGreen) / 9.);
                int avg_rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j +
                                                1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i +
                                                        1][j + 1].rgbtBlue) / 9.);

                image[i][j].rgbtRed = avg_rgbtRed;
                image[i][j].rgbtGreen = avg_rgbtGreen;
                image[i][j].rgbtBlue = avg_rgbtBlue;
            }

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
// create copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // loop through image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize conditional logic
            int ignore_top_row = 0;
            int ignore_bottom_row = 0;
            int ignore_left_column = 0;
            int ignore_right_column = 0;

            if ((i - 1) < 0)
            {
                ignore_top_row += 1;
            }
            if ((i + 1) == height)
            {
                ignore_bottom_row += 1;
            }
            if ((j - 1) < 0)
            {
                ignore_left_column += 1;
            }
            if ((j + 1) == width)
            {
                ignore_right_column += 1;
            }

            if (ignore_top_row == 1 && ignore_left_column == 1) // Top Left
            {
                // GX
                int red_Gx = (int) round((0 * -1) +
                                         (0 * 0) +
                                         (0 * 1) +
                                         (0 * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 2) +
                                         (0 * -1) +
                                         (copy[i + 1][j].rgbtRed * 0) +
                                         (copy[i + 1][j + 1].rgbtRed * 1));

                int green_Gx = (int) round((0 * -1) +
                                           (0 * 0) +
                                           (0 * 1) +
                                           (0 * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 2) +
                                           (0 * -1) +
                                           (copy[i + 1][j].rgbtGreen * 0) +
                                           (copy[i + 1][j + 1].rgbtGreen * 1));

                int blue_Gx = (int) round((0 * -1) +
                                          (0 * 0) +
                                          (0 * 1) +
                                          (0 * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 2) +
                                          (0 * -1) +
                                          (copy[i + 1][j].rgbtBlue * 0) +
                                          (copy[i + 1][j + 1].rgbtBlue * 1));

                // GY
                int red_Gy = (int) round((0 * -1) +
                                         (0 * -2) +
                                         (0 * -1) +
                                         (0 * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 0) +
                                         (0 * 1) +
                                         (copy[i + 1][j].rgbtRed * 2) +
                                         (copy[i + 1][j + 1].rgbtRed * 1));

                int green_Gy = (int) round((0 * -1) +
                                           (0 * -2) +
                                           (0 * -1) +
                                           (0 * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 0) +
                                           (0 * 1) +
                                           (copy[i + 1][j].rgbtGreen * 2) +
                                           (copy[i + 1][j + 1].rgbtGreen * 1));

                int blue_Gy = (int) round((0 * -1) +
                                          (0 * -2) +
                                          (0 * -1) +
                                          (0 * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 0) +
                                          (0 * 1) +
                                          (copy[i + 1][j].rgbtBlue * 2) +
                                          (copy[i + 1][j + 1].rgbtBlue * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }

            }
            else if (ignore_top_row == 1 && ignore_right_column == 1) // Top Right
            {
                // GX
                int red_Gx = (int) round((0 * -1) +
                                         (0 * 0) +
                                         (0 * 1) +
                                         (copy[i][j - 1].rgbtRed * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (0 * 2) +
                                         (copy[i + 1][j - 1].rgbtRed * -1) +
                                         (copy[i + 1][j].rgbtRed * 0) +
                                         (0 * 1));

                int green_Gx = (int) round((0 * -1) +
                                           (0 * 0) +
                                           (0 * 1) +
                                           (copy[i][j - 1].rgbtGreen * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (0 * 2) +
                                           (copy[i + 1][j - 1].rgbtGreen * -1) +
                                           (copy[i + 1][j].rgbtGreen * 0) +
                                           (0 * 1));

                int blue_Gx = (int) round((0 * -1) +
                                          (0 * 0) +
                                          (0 * 1) +
                                          (copy[i][j - 1].rgbtBlue * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (0 * 2) +
                                          (copy[i + 1][j - 1].rgbtBlue * -1) +
                                          (copy[i + 1][j].rgbtBlue * 0) +
                                          (0 * 1));

                // GY
                int red_Gy = (int) round((0 * -1) +
                                         (0 * -2) +
                                         (0 * -1) +
                                         (copy[i][j - 1].rgbtRed * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (0 * 0) +
                                         (copy[i + 1][j - 1].rgbtRed * 1) +
                                         (copy[i + 1][j].rgbtRed * 2) +
                                         (0 * 1));

                int green_Gy = (int) round((0 * -1) +
                                           (0 * -2) +
                                           (0 * -1) +
                                           (copy[i][j - 1].rgbtGreen * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (0 * 0) +
                                           (copy[i + 1][j - 1].rgbtGreen * 1) +
                                           (copy[i + 1][j].rgbtGreen * 2) +
                                           (0 * 1));

                int blue_Gy = (int) round((0 * -1) +
                                          (0 * -2) +
                                          (0 * -1) +
                                          (copy[i][j - 1].rgbtBlue * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (0 * 0) +
                                          (copy[i + 1][j - 1].rgbtBlue * 1) +
                                          (copy[i + 1][j].rgbtBlue * 2) +
                                          (0 * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }

            }
            else if (ignore_left_column == 1 && ignore_bottom_row == 1) // Bottom Left
            {
                // GX
                int red_Gx = (int) round((0 * -1) +
                                         (copy[i - 1][j].rgbtRed * 0) +
                                         (copy[i - 1][j + 1].rgbtRed * 1) +
                                         (0 * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 2) +
                                         (0 * -1) +
                                         (0 * 0) +
                                         (0 * 1));

                int green_Gx = (int) round((0 * -1) +
                                           (copy[i - 1][j].rgbtGreen * 0) +
                                           (copy[i - 1][j + 1].rgbtGreen * 1) +
                                           (0 * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 2) +
                                           (0 * -1) +
                                           (0 * 0) +
                                           (0 * 1));

                int blue_Gx = (int) round((0 * -1) +
                                          (copy[i - 1][j].rgbtBlue * 0) +
                                          (copy[i - 1][j + 1].rgbtBlue * 1) +
                                          (0 * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 2) +
                                          (0 * -1) +
                                          (0 * 0) +
                                          (0 * 1));

                // GY
                int red_Gy = (int) round((0 * -1) +
                                         (copy[i - 1][j].rgbtRed * -2) +
                                         (copy[i - 1][j + 1].rgbtRed * -1) +
                                         (0 * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 0) +
                                         (0 * 1) +
                                         (0 * 2) +
                                         (0 * 1));

                int green_Gy = (int) round((0 * -1) +
                                           (copy[i - 1][j].rgbtGreen * -2) +
                                           (copy[i - 1][j + 1].rgbtGreen * -1) +
                                           (0 * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 0) +
                                           (0 * 1) +
                                           (0 * 2) +
                                           (0 * 1));

                int blue_Gy = (int) round((0 * -1) +
                                          (copy[i - 1][j].rgbtBlue * -2) +
                                          (copy[i - 1][j + 1].rgbtBlue * -1) +
                                          (0 * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 0) +
                                          (0 * 1) +
                                          (0 * 2) +
                                          (0 * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }

            }
            else if (ignore_right_column == 1 && ignore_bottom_row == 1) // Bottom Right
            {
                // GX
                int red_Gx = (int) round((copy[i - 1][j - 1].rgbtRed * -1) +
                                         (copy[i - 1][j].rgbtRed * 0) +
                                         (0 * 1) +
                                         (copy[i][j - 1].rgbtRed * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (0 * 2) +
                                         (0 * -1) +
                                         (0 * 0) +
                                         (0 * 1));

                int green_Gx = (int) round((copy[i - 1][j - 1].rgbtGreen * -1) +
                                           (copy[i - 1][j].rgbtGreen * 0) +
                                           (0 * 1) +
                                           (copy[i][j - 1].rgbtGreen * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (0 * 2) +
                                           (0 * -1) +
                                           (0 * 0) +
                                           (0 * 1));

                int blue_Gx = (int) round((copy[i - 1][j - 1].rgbtBlue * -1) +
                                          (copy[i - 1][j].rgbtBlue * 0) +
                                          (0 * 1) +
                                          (copy[i][j - 1].rgbtBlue * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (0 * 2) +
                                          (0 * -1) +
                                          (0 * 0) +
                                          (0 * 1));

                // GY
                int red_Gy = (int) round((copy[i - 1][j - 1].rgbtRed * -1) +
                                         (copy[i - 1][j].rgbtRed * -2) +
                                         (0 * -1) +
                                         (copy[i][j - 1].rgbtRed * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (0 * 0) +
                                         (0 * 1) +
                                         (0 * 2) +
                                         (0 * 1));

                int green_Gy = (int) round((copy[i - 1][j - 1].rgbtGreen * -1) +
                                           (copy[i - 1][j].rgbtGreen * -2) +
                                           (0 * -1) +
                                           (copy[i][j - 1].rgbtGreen * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (0 * 0) +
                                           (0 * 1) +
                                           (0 * 2) +
                                           (0 * 1));

                int blue_Gy = (int) round((copy[i - 1][j - 1].rgbtBlue * -1) +
                                          (copy[i - 1][j].rgbtBlue * -2) +
                                          (0 * -1) +
                                          (copy[i][j - 1].rgbtBlue * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (0 * 0) +
                                          (0 * 1) +
                                          (0 * 2) +
                                          (0 * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }

            }
            else if (ignore_top_row == 1 && ignore_left_column == 0 && ignore_right_column == 0) // Top (not corner)
            {
                // GX
                int red_Gx = (int) round((0 * -1) +
                                         (0 * 0) +
                                         (0 * 1) +
                                         (copy[i][j - 1].rgbtRed * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 2) +
                                         (copy[i + 1][j - 1].rgbtRed * -1) +
                                         (copy[i + 1][j].rgbtRed * 0) +
                                         (copy[i + 1][j + 1].rgbtRed * 1));

                int green_Gx = (int) round((0 * -1) +
                                           (0 * 0) +
                                           (0 * 1) +
                                           (copy[i][j - 1].rgbtGreen * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 2) +
                                           (copy[i + 1][j - 1].rgbtGreen * -1) +
                                           (copy[i + 1][j].rgbtGreen * 0) +
                                           (copy[i + 1][j + 1].rgbtGreen * 1));

                int blue_Gx = (int) round((0 * -1) +
                                          (0 * 0) +
                                          (0 * 1) +
                                          (copy[i][j - 1].rgbtBlue * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 2) +
                                          (copy[i + 1][j - 1].rgbtBlue * -1) +
                                          (copy[i + 1][j].rgbtBlue * 0) +
                                          (copy[i + 1][j + 1].rgbtBlue * 1));

                // GY
                int red_Gy = (int) round((0 * -1) +
                                         (0 * -2) +
                                         (0 * -1) +
                                         (copy[i][j - 1].rgbtRed * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 0) +
                                         (copy[i + 1][j - 1].rgbtRed * 1) +
                                         (copy[i + 1][j].rgbtRed * 2) +
                                         (copy[i + 1][j + 1].rgbtRed * 1));

                int green_Gy = (int) round((0 * -1) +
                                           (0 * -2) +
                                           (0 * -1) +
                                           (copy[i][j - 1].rgbtGreen * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 0) +
                                           (copy[i + 1][j - 1].rgbtGreen * 1) +
                                           (copy[i + 1][j].rgbtGreen * 2) +
                                           (copy[i + 1][j + 1].rgbtGreen * 1));

                int blue_Gy = (int) round((0 * -1) +
                                          (0 * -2) +
                                          (0 * -1) +
                                          (copy[i][j - 1].rgbtBlue * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 0) +
                                          (copy[i + 1][j - 1].rgbtBlue * 1) +
                                          (copy[i + 1][j].rgbtBlue * 2) +
                                          (copy[i + 1][j + 1].rgbtBlue * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }

            }
            else if (ignore_left_column == 1 && ignore_top_row == 0 && ignore_bottom_row == 0) // Left (not corner)
            {
                // GX
                int red_Gx = (int) round((0 * -1) +
                                         (copy[i - 1][j].rgbtRed * 0) +
                                         (copy[i - 1][j + 1].rgbtRed * 1) +
                                         (0 * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 2) +
                                         (0 * -1) +
                                         (copy[i + 1][j].rgbtRed * 0) +
                                         (copy[i + 1][j + 1].rgbtRed * 1));

                int green_Gx = (int) round((0 * -1) +
                                           (copy[i - 1][j].rgbtGreen * 0) +
                                           (copy[i - 1][j + 1].rgbtGreen * 1) +
                                           (0 * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 2) +
                                           (0 * -1) +
                                           (copy[i + 1][j].rgbtGreen * 0) +
                                           (copy[i + 1][j + 1].rgbtGreen * 1));

                int blue_Gx = (int) round((0 * -1) +
                                          (copy[i - 1][j].rgbtBlue * 0) +
                                          (copy[i - 1][j + 1].rgbtBlue * 1) +
                                          (0 * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 2) +
                                          (0 * -1) +
                                          (copy[i + 1][j].rgbtBlue * 0) +
                                          (copy[i + 1][j + 1].rgbtBlue * 1));

                // GY
                int red_Gy = (int) round((0 * -1) +
                                         (copy[i - 1][j].rgbtRed * -2) +
                                         (copy[i - 1][j + 1].rgbtRed * -1) +
                                         (0 * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 0) +
                                         (0 * 1) +
                                         (copy[i + 1][j].rgbtRed * 2) +
                                         (copy[i + 1][j + 1].rgbtRed * 1));

                int green_Gy = (int) round((0 * -1) +
                                           (copy[i - 1][j].rgbtGreen * -2) +
                                           (copy[i - 1][j + 1].rgbtGreen * -1) +
                                           (0 * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 0) +
                                           (0 * 1) +
                                           (copy[i + 1][j].rgbtGreen * 2) +
                                           (copy[i + 1][j + 1].rgbtGreen * 1));

                int blue_Gy = (int) round((0 * -1) +
                                          (copy[i - 1][j].rgbtBlue * -2) +
                                          (copy[i - 1][j + 1].rgbtBlue * -1) +
                                          (0 * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 0) +
                                          (0 * 1) +
                                          (copy[i + 1][j].rgbtBlue * 2) +
                                          (copy[i + 1][j + 1].rgbtBlue * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }

            }
            else if (ignore_right_column == 1 && ignore_top_row == 0 && ignore_bottom_row == 0) // Right (not corner)
            {
                // GX
                int red_Gx = (int) round((copy[i - 1][j - 1].rgbtRed * -1) +
                                         (copy[i - 1][j].rgbtRed * 0) +
                                         (0 * 1) +
                                         (copy[i][j - 1].rgbtRed * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (0 * 2) +
                                         (copy[i + 1][j - 1].rgbtRed * -1) +
                                         (copy[i + 1][j].rgbtRed * 0) +
                                         (0 * 1));

                int green_Gx = (int) round((copy[i - 1][j - 1].rgbtGreen * -1) +
                                           (copy[i - 1][j].rgbtGreen * 0) +
                                           (0 * 1) +
                                           (copy[i][j - 1].rgbtGreen * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (0 * 2) +
                                           (copy[i + 1][j - 1].rgbtGreen * -1) +
                                           (copy[i + 1][j].rgbtGreen * 0) +
                                           (0 * 1));

                int blue_Gx = (int) round((copy[i - 1][j - 1].rgbtBlue * -1) +
                                          (copy[i - 1][j].rgbtBlue * 0) +
                                          (0 * 1) +
                                          (copy[i][j - 1].rgbtBlue * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (0 * 2) +
                                          (copy[i + 1][j - 1].rgbtBlue * -1) +
                                          (copy[i + 1][j].rgbtBlue * 0) +
                                          (0 * 1));

                // GY
                int red_Gy = (int) round((copy[i - 1][j - 1].rgbtRed * -1) +
                                         (copy[i - 1][j].rgbtRed * -2) +
                                         (0 * -1) +
                                         (copy[i][j - 1].rgbtRed * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (0 * 0) +
                                         (copy[i + 1][j - 1].rgbtRed * 1) +
                                         (copy[i + 1][j].rgbtRed * 2) +
                                         (0 * 1));

                int green_Gy = (int) round((copy[i - 1][j - 1].rgbtGreen * -1) +
                                           (copy[i - 1][j].rgbtGreen * -2) +
                                           (0 * -1) +
                                           (copy[i][j - 1].rgbtGreen * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (0 * 0) +
                                           (copy[i + 1][j - 1].rgbtGreen * 1) +
                                           (copy[i + 1][j].rgbtGreen * 2) +
                                           (0 * 1));

                int blue_Gy = (int) round((copy[i - 1][j - 1].rgbtBlue * -1) +
                                          (copy[i - 1][j].rgbtBlue * -2) +
                                          (0 * -1) +
                                          (copy[i][j - 1].rgbtBlue * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (0 * 0) +
                                          (copy[i + 1][j - 1].rgbtBlue * 1) +
                                          (copy[i + 1][j].rgbtBlue * 2) +
                                          (0 * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }

            }
            else if (ignore_bottom_row == 1 && ignore_left_column == 0 && ignore_right_column == 0) // Bottom (not corner)
            {
                // GX
                int red_Gx = (int) round((copy[i - 1][j - 1].rgbtRed * -1) +
                                         (copy[i - 1][j].rgbtRed * 0) +
                                         (copy[i - 1][j + 1].rgbtRed * 1) +
                                         (copy[i][j - 1].rgbtRed * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 2) +
                                         (0 * -1) +
                                         (0 * 0) +
                                         (0 * 1));

                int green_Gx = (int) round((copy[i - 1][j - 1].rgbtGreen * -1) +
                                           (copy[i - 1][j].rgbtGreen * 0) +
                                           (copy[i - 1][j + 1].rgbtGreen * 1) +
                                           (copy[i][j - 1].rgbtGreen * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 2) +
                                           (0 * -1) +
                                           (0 * 0) +
                                           (0 * 1));

                int blue_Gx = (int) round((copy[i - 1][j - 1].rgbtBlue * -1) +
                                          (copy[i - 1][j].rgbtBlue * 0) +
                                          (copy[i - 1][j + 1].rgbtBlue * 1) +
                                          (copy[i][j - 1].rgbtBlue * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 2) +
                                          (0 * -1) +
                                          (0 * 0) +
                                          (0 * 1));

                // GY
                int red_Gy = (int) round((copy[i - 1][j - 1].rgbtRed * -1) +
                                         (copy[i - 1][j].rgbtRed * -2) +
                                         (copy[i - 1][j + 1].rgbtRed * -1) +
                                         (copy[i][j - 1].rgbtRed * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 0) +
                                         (0 * 1) +
                                         (0 * 2) +
                                         (0 * 1));

                int green_Gy = (int) round((copy[i - 1][j - 1].rgbtGreen * -1) +
                                           (copy[i - 1][j].rgbtGreen * -2) +
                                           (copy[i - 1][j + 1].rgbtGreen * -1) +
                                           (copy[i][j - 1].rgbtGreen * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 0) +
                                           (0 * 1) +
                                           (0 * 2) +
                                           (0 * 1));

                int blue_Gy = (int) round((copy[i - 1][j - 1].rgbtBlue * -1) +
                                          (copy[i - 1][j].rgbtBlue * -2) +
                                          (copy[i - 1][j + 1].rgbtBlue * -1) +
                                          (copy[i][j - 1].rgbtBlue * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 0) +
                                          (0 * 1) +
                                          (0 * 2) +
                                          (0 * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }

            }

            else // Center Pixel
            {
                // GX
                int red_Gx = (int) round((copy[i - 1][j - 1].rgbtRed * -1) +
                                         (copy[i - 1][j].rgbtRed * 0) +
                                         (copy[i - 1][j + 1].rgbtRed * 1) +
                                         (copy[i][j - 1].rgbtRed * -2) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 2) +
                                         (copy[i + 1][j - 1].rgbtRed * -1) +
                                         (copy[i + 1][j].rgbtRed * 0) +
                                         (copy[i + 1][j + 1].rgbtRed * 1));

                int green_Gx = (int) round((copy[i - 1][j - 1].rgbtGreen * -1) +
                                           (copy[i - 1][j].rgbtGreen * 0) +
                                           (copy[i - 1][j + 1].rgbtGreen * 1) +
                                           (copy[i][j - 1].rgbtGreen * -2) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 2) +
                                           (copy[i + 1][j - 1].rgbtGreen * -1) +
                                           (copy[i + 1][j].rgbtGreen * 0) +
                                           (copy[i + 1][j + 1].rgbtGreen * 1));

                int blue_Gx = (int) round((copy[i - 1][j - 1].rgbtBlue * -1) +
                                          (copy[i - 1][j].rgbtBlue * 0) +
                                          (copy[i - 1][j + 1].rgbtBlue * 1) +
                                          (copy[i][j - 1].rgbtBlue * -2) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 2) +
                                          (copy[i + 1][j - 1].rgbtBlue * -1) +
                                          (copy[i + 1][j].rgbtBlue * 0) +
                                          (copy[i + 1][j + 1].rgbtBlue * 1));

                // GY
                int red_Gy = (int) round((copy[i - 1][j - 1].rgbtRed * -1) +
                                         (copy[i - 1][j].rgbtRed * -2) +
                                         (copy[i - 1][j + 1].rgbtRed * -1) +
                                         (copy[i][j - 1].rgbtRed * 0) +
                                         (copy[i][j].rgbtRed * 0) +
                                         (copy[i][j + 1].rgbtRed * 0) +
                                         (copy[i + 1][j - 1].rgbtRed * 1) +
                                         (copy[i + 1][j].rgbtRed * 2) +
                                         (copy[i + 1][j + 1].rgbtRed * 1));

                int green_Gy = (int) round((copy[i - 1][j - 1].rgbtGreen * -1) +
                                           (copy[i - 1][j].rgbtGreen * -2) +
                                           (copy[i - 1][j + 1].rgbtGreen * -1) +
                                           (copy[i][j - 1].rgbtGreen * 0) +
                                           (copy[i][j].rgbtGreen * 0) +
                                           (copy[i][j + 1].rgbtGreen * 0) +
                                           (copy[i + 1][j - 1].rgbtGreen * 1) +
                                           (copy[i + 1][j].rgbtGreen * 2) +
                                           (copy[i + 1][j + 1].rgbtGreen * 1));

                int blue_Gy = (int) round((copy[i - 1][j - 1].rgbtBlue * -1) +
                                          (copy[i - 1][j].rgbtBlue * -2) +
                                          (copy[i - 1][j + 1].rgbtBlue * -1) +
                                          (copy[i][j - 1].rgbtBlue * 0) +
                                          (copy[i][j].rgbtBlue * 0) +
                                          (copy[i][j + 1].rgbtBlue * 0) +
                                          (copy[i + 1][j - 1].rgbtBlue * 1) +
                                          (copy[i + 1][j].rgbtBlue * 2) +
                                          (copy[i + 1][j + 1].rgbtBlue * 1));

                int final_red = (int) round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
                int final_green = (int) round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
                int final_blue = (int) round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

                if (final_red <= 255)
                {
                    image[i][j].rgbtRed = final_red;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                if (final_green <= 255)
                {
                    image[i][j].rgbtGreen = final_green;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                if (final_blue <= 255)
                {
                    image[i][j].rgbtBlue = final_blue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

        }
    }
    return;
}
