#include "imageToNeural.h"
#include <err.h>

void imageToNeural(SDL_Surface *img, float array[SIZE])
{
    size_t counter = 0;
    for(int i = 0; i< SIZE;i++)
        array[i] = 0;
    for(int x = 0; x < img->w; x++)
    {
        for(int y = 0; y < img->h;y++)
        {
            
            Uint32 pixel = get_pixel(img,x,y);
            Uint8 r,g,b;
            SDL_GetRGB(pixel,img->format,&r,&g,&b);
            float colour = (float) ((r + g + b )/ 3);
            array[counter] = colour;
            counter++;
        }
    }
}


SDL_Surface *loadImage(char *path)
{
    SDL_Surface *image = NULL;
    image = IMG_Load(path);
    if (!image)
        errx(3, "can't load %s: %s", path, IMG_GetError());
    return image;
}
