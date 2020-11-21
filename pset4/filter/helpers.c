#include "helpers.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct
{
    int red;
    int green;
    int blue;
}
RGB;


RGBTRIPLE applyKernel2(int height, int width, int x, int y, RGBTRIPLE paddedImage[height][width], float kernelX[3][3],
                       float kernelY[3][3])
{
    RGBTRIPLE filteredPixel;

    RGB color, colorX, colorY;

    memset(&color, 0, sizeof(color));
    memset(&colorX, 0, sizeof(colorX));
    memset(&colorY, 0, sizeof(colorY));


    for (size_t kh = 0; kh < 3; ++kh)
    {
        for (size_t kw = 0; kw < 3; ++kw)
        {
            colorX.blue += (paddedImage[x + kh][y + kw].rgbtBlue * kernelX[kh][kw]);
            colorY.blue += (paddedImage[x + kh][y + kw].rgbtBlue * kernelY[kh][kw]);
            colorX.green += (paddedImage[x + kh][y + kw].rgbtGreen * kernelX[kh][kw]);
            colorY.green += (paddedImage[x + kh][y + kw].rgbtGreen * kernelY[kh][kw]);
            colorX.red += (paddedImage[x + kh][y + kw].rgbtRed * kernelX[kh][kw]);
            colorY.red += (paddedImage[x + kh][y + kw].rgbtRed * kernelY[kh][kw]);
        }
    }

    color.blue = round(sqrt(colorX.blue * colorX.blue + colorY.blue * colorY.blue));
    color.green = round(sqrt(colorX.green * colorX.green + colorY.green * colorY.green));
    color.red = round(sqrt(colorX.red * colorX.red + colorY.red * colorY.red));

    filteredPixel.rgbtBlue = color.blue > 255 ? 255 : color.blue;
    filteredPixel.rgbtGreen = color.green > 255 ? 255 : color.green;
    filteredPixel.rgbtRed = color.red > 255 ? 255 : color.red;

    return filteredPixel;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float pixelAverage;

    for (size_t h = 0; h < height; ++h)
    {
        for (size_t w = 0; w < width; ++w)
        {
            pixelAverage = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.);

            image[h][w].rgbtBlue  = pixelAverage;
            image[h][w].rgbtGreen = pixelAverage;
            image[h][w].rgbtRed   = pixelAverage;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    memset(temp, 0, sizeof(temp));

    for (size_t h = 0; h < height; ++h)
    {
        for (size_t w = 0; w < width; ++w)
        {
            temp[h][w] = image[h][width - w - 1];
        }
    }

    memcpy(image, temp, sizeof(temp));

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE filteredPixel;

    RGBTRIPLE temp[height][width];

    RGB color;

    memset(&color, 0, sizeof(color));

    memcpy(temp, image, sizeof(temp));

    float pixelCount = 0.;

    for (size_t h = 0; h < height; ++h)
    {
        for (size_t w = 0; w < width; ++w)
        {
            for (int kh = -1; kh < 2; ++kh)
            {
                for (int kw = -1; kw < 2; ++kw)
                {
                    if (((h + kh) >= 0) && ((h + kh) < height))
                    {
                        if (((w + kw) >= 0) && ((w + kw) < width))
                        {
                            color.blue += image[h + kh][w + kw].rgbtBlue;
                            color.green += image[h + kh][w + kw].rgbtGreen;
                            color.red += image[h + kh][w + kw].rgbtRed;
                            pixelCount++;
                        }
                    }
                }
            }

            filteredPixel.rgbtBlue = round(color.blue / pixelCount);
            filteredPixel.rgbtGreen = round(color.green / pixelCount);
            filteredPixel.rgbtRed = round(color.red / pixelCount);

            temp[h][w] = filteredPixel;

            pixelCount = 0;
            memset(&color, 0, sizeof(color));
        }
    }

    memcpy(image, temp, sizeof(temp));


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float gxKernel[3][3] = {{-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    float gyKernel[3][3] = {{-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


    RGB filteredPixelx;
    RGB filteredPixely;

    RGBTRIPLE filteredPixel;

    RGBTRIPLE paddedImage[height + 2][width + 2];

    memset(paddedImage, 0, sizeof(paddedImage));

    for (size_t h = 0; h < height; ++h)
    {
        for (size_t w = 0; w < width; ++w)
        {
            paddedImage[h + 1][w + 1] = image[h][w];
        }
    }

    for (size_t h = 0; h < height; ++h)
    {
        for (size_t w = 0; w < width; ++w)
        {
            filteredPixel = applyKernel2(height + 2, width + 2, h, w, paddedImage, gxKernel, gyKernel);

            image[h][w] = filteredPixel;
        }
    }

    return;
}