#include "pixel_operations.h"
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void grayscale(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;
    Uint32 pixel;
    Uint8 r, g, b, av;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            av = 0.3 * r + 0.59 * g + 0.11 * b;
            pixel = SDL_MapRGB(image->format, av, av, av);
            put_pixel(image, x, y, pixel);
        }
    }
}

/*
SDL_Surface* blackWhite(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;
    Uint32 pixel;
    Uint8 r, g, b;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if(r < 128)
            {
                r = 0;
            }
            else
            {
                r = 255;
            }
            pixel = SDL_MapRGB(image->format, r, r, r);
            put_pixel(image, x, y, pixel);
        }
    }
    return image;
}*/
