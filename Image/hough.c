#include <err.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "hough.h"
#include "display.h"

// converts degree to radian
double to_radian(int degree)
{
    return degree * (M_PI / 180.0);
}

/*
  image : sobel image
  accumulator : matrix to store the coordinates of the lines
*/
void houghTransform(SDL_Surface* image, int accumulator[][181])
{
    int width = image->w;
    int height = image->h;
    int r_max = (int) sqrt(width * width + height * height);
    double rho, rad;
    Uint32 pixel;
    Uint8 r, g, b;
    int nb_r = 0;
    // iterate through the pixels of the image
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            // get the color of the pixel
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            // enter if the pixel is white
            if(r > 0)
            {
                nb_r++;
                for(int theta = -90; theta < 91; theta++)
               {
                    rad = to_radian(theta);
                    rho = x * cos(rad) + y * sin(rad);
                    // +1 in accumulator for each theta for each point
                    accumulator[(int) rho + r_max][theta + 90] += 1;
                    //if(accumulator[(int) rho + r_max][theta] > 10)
                    // printf("accumulator[%d][%d] = %d\n", (int) rho + r_max, theta,  accumulator[(int) rho + r_max][theta]);
                }
            }
        }
    }
    //printf("nb_r = %d\n", nb_r);
}

/*
  accumulator : a matrix with the values of rho and teta
  rows : the maximum number of rows of the matrix
  cols : the maximum number of columns of the matrix
  coord : the coordinates of maximum value in accumulator matrix = values of rho and theta for each line of the sudoku => polar coordinates
  -------------
  returns : the len of coord
*/
void coordinates(int accumulator[][181], int rows, int cols)
{
    int max = 0;
    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < cols; i++)
        {
            if(accumulator[j][i] > max)
                max = accumulator[j][i];
        }
    }
    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            if(accumulator[y][x] < max-300)
            {
                accumulator[y][x] = 0;
            }
            else if (accumulator[y][x] > 100)
                printf("accumulator value = %d\n", accumulator[y][x]);
        }
    }
    printf("coordinates done\n");
}

/*
  image : the image on which we applied the hough function
  accumulator : a matrix with the values of rho and teta
  rows : the maximum number of rows of the matrix
  cols : the maximum number of columns of the matrix
  coord : coordinates of the maximum value in the accumulator = values of rho and theta are the polar coordinates of a line
  size_c : length of coordinates array

void drawHough(SDL_Surface* image, int** accumulator, int rows, int cols)
{
    int x, y;
    double rho, rad;
    // j'ai plus d'idees, il est 7h je vais me coucher
}
*/

void DrawLines(SDL_Surface* image)
{
    int width = image->w;
    printf("width = %d\n", width);
    int height = image->h;
    printf("height = %d\n", height);
    int rho = (int) sqrt(width * width + height * height);
    int w = 181;
    int h = 2*rho+1;
    printf("rho = %d\n", h);
    int accumulator[h][w];
    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            accumulator[j][i] = 0;
        }
    }
    houghTransform(image, accumulator);
    coordinates(accumulator, h, w);
    double x, y;
    float a, b, origin, slope;
    int x1, y1, x2, y2;
    Uint32 pixel;
    printf("before loop\n");
    for(int j = 0; j < h; j++)
    {
        //printf("j == %d\n", j);
        for(int i = 0; i < w; i++)
        {
            //printf("i == %d\n", i);
            //printf("accumulator[%d][%d] = %d\n", j, i, accumulator[j][i]);
            if(accumulator[j][i] > 0)
            {
                printf("accumulator[%d][%d] = %d\n", j, i, accumulator[j][i]);
                a = cos(to_radian(i-90));
                b = sin(to_radian(i-90));
                x = a * j;
                y = b * j;
                x1 = (int)x + 1000*(-b);
                y1 = (int)y + 1000*a;
                //printf("x1 = %d, y1 = %d\n", x1, y1);
                x2 = (int)x - 1000*(-b);
                y2 = (int)y - 1000*a;
                //printf("x2 = %d, y2 = %d\n", x2, y2);
                //printf("y2 - y1 = %d\n", y2-y1);
                //printf("x2 - x1 = %d\n", x2-x1);
                if(x1 == x2)
                {
                    slope = 1;
                    origin = 0;
                }
                else
                {
                    slope = (float)(y2-y1)/(x2-x1);
                    origin = y2 - slope * x2;
                }
                //printf("origin = %f\n", origin);
                //printf("origin should be = %f\n", y2 - slope * x2);
                //printf("slope = %f\n", slope);
                for(int n = 0; n < width; n++)
                    {
                        y2 = (int)slope * n + origin;
                        printf("y2 = %d\n", y2);
                        if(y2 >= 0 && y2 < height)
                        {
                            //printf("y2 = %d\n", y2);
                            pixel = SDL_MapRGB(image->format, 255, 0, 0);
                            //printf("x = %d, y = %d\n", n, y2);
                            put_pixel(image, n, y2, pixel);
                        }
                    }
                printf("y2 - y1 = %d\n", y2-y1);
                printf("x2 - x1 = %d\n", x2-x1);
                printf("origin = %f\n", origin);
                printf("slope = %f\n", slope);
            }
        }
    }
}

void HoughMain(SDL_Surface* image)
{
    int width = image->w;
    printf("width = %d\n", width);
    int height = image->h;
    printf("height = %d\n", height);
    int rho = (int) sqrt(width * width + height * height);
    int w = 181;
    int h = 2*rho+1;
    printf("rho = %d\n", h);
    int accumulator[h][w];
    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            accumulator[j][i] = 0;
        }
    }
    houghTransform(image, accumulator);
    DrawLines(image);
    printf("printed lines\n");
    SDL_Surface *bimage = SDL_CreateRGBSurface(0, 180, 2*rho, 32, 0, 0, 0, 0);
    int val;
    Uint32 pixel;
     printf("after creating image\n");
    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            val = accumulator[j][i];
            pixel = SDL_MapRGB(bimage->format, val, val, val);
            put_pixel(bimage, i, j, pixel);
        }
    }
    SDL_Surface *n_image = display_image(bimage);
    wait_for_keypressed();
    SDL_FreeSurface(n_image);
    SDL_FreeSurface(bimage);
    SDL_Surface *biimage = display_image(image);
    wait_for_keypressed();
    SDL_FreeSurface(biimage);
}

// https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
// https://docs.opencv.org/3.4/da/d22/tutorial_py_canny.html
