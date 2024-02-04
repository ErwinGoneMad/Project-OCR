#include <err.h>
#include <math.h>
#include "pixel_operations.h"
#include "sobel_filter.h"

int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
size_t size_ke = 9;

int gradient(int x, int y)
{
    double a = sqrt(x * x + y * y);
    return (int) a;
}

int updatePixel2(int pixels[])
{
    int x = 0;
    int y = 0;
    int g = 0;
    for (size_t i = 0; i < size_ke; i++)
    {
        x += (pixels[i] * Gx[i]);
        y += (pixels[i] * Gy[i]);
    }
    //printf("x = %d\n", x);
    g = gradient(x, y);
    return g;
}


void Sfilter(SDL_Surface* image, SDL_Surface* n_image)
{
    int width = image->w;
    int height = image->h;
    Uint32 pixel;
    int pixels[9];
    Uint8 r, g, b;
    int i;
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            i = 0;
            for (int c = y - 1; c <= y + 1; c++)
            {
                for (int a = x - 1; a <= x + 1; a++)
                {
                    pixel = get_pixel(image, a, c);
                    SDL_GetRGB(pixel, image->format, &r, &g, &b);
                    pixels[i] = r;
                    i++;
                }
            }
            r = updatePixel2(pixels);
            pixel = SDL_MapRGB(image->format, r, r, r);
            put_pixel(n_image, x, y, pixel);
        }
    }
}
