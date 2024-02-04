#include <err.h>
#include <math.h>
#include "pixel_operations.h"
#include "gaussian_filter.h"

Uint8 kernel[] = {2, 4, 5, 4, 2, 4, 9, 12, 9, 4, 5, 12, 15, 12, 5, 4, 9, 12, 9, 4, 2, 4, 5, 4, 2};
size_t size_k = 25;
Uint8 maxval = 160;

// updates the kernel with its exact values
void updateKernel()
{
    for(size_t i = 0; i < size_k; i++)
    {
        kernel[i] += kernel[i] * (float)1/159;
    }
}

/*
 * Function: updatePixel
 * ----------------------------
 *   takes a list of pixels of the image and finds a new pixel value
 *
 *    image[] = pixel values
 *    .....
 *
 *   returns: a new pixel value
 */
int updatePixel(Uint8 image[])
{
    int pixel = 0;
    int val = 0;
    // multiplication of the values of the pixels with the kernel values
    for(size_t i = 0; i < size_k; i++)
    {
        val = (image[i] * kernel[i]);
        pixel += val;
    }
    // average =  new value of pixel
    pixel = pixel/maxval;
    return pixel;
}

/*
 * Function: Filter
 * ----------------------------
 *   Applies the Gaussian filter to an image
 *
 *    image : the surface of an image
 *    .....
 *
 *   returns: should return the image with the noise removed
 */
void filter(SDL_Surface* image, SDL_Surface* n_image)
{
    //updateKernel();
    int width = image->w;
    int height = image->h;
    Uint32 pixel;
    Uint8 pixels[25];
    Uint8 r, g, b;
    int i;
    for(int y = 2; y < height-2; y++)
    {
        for(int x = 2; x < width-2; x++)
        {
            i = 0;
            for(int c = y-2; c <= y+2; c++)
            {
                for(int a = x-2; a <= x+2; a++)
                {
                    pixel = get_pixel(image, a, c);
                    SDL_GetRGB(pixel, image->format, &r, &g, &b);
                    pixels[i] = r;
                    i++;
                }
            }
            r = updatePixel(pixels);
            pixel = SDL_MapRGB(image->format, r, r, r);
            put_pixel(n_image, x, y, pixel);
        }
    }
}
