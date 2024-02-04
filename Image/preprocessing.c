#include <err.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "display.h"
#include "remove_color.h"
#include "gaussian_filter.h"
#include "sobel_filter.h"
#include "hough.h"
#include "preprocessing.h"

const char *preprocess(SDL_Surface *image)
{
    /*if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
        SDL_Surface *image = loadImage(path);*/
    int width = image->w;
    int height = image->h;
    grayscale(image);
    SDL_Surface *bimage = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    filter(image, bimage);
    Sfilter(bimage, image);
    char *path2 = "image.bmp";
    if(SDL_SaveBMP(image, path2) != 0)
    {
        // Error saving bitmap
        printf("SDL_SaveBMP failed: %s\n", SDL_GetError());
    }
    return path2;
}
