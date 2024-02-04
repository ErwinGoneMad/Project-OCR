#include <err.h>
#include <math.h>
#include "pixel_operations.h"
#include "split.h"

// positions = array for Y pos -> length of the height of the image = rempli de 1
void positionsY(SDL_Surface* image, int pos[])
{
    int width = image->w;
    int height = image->h;
    int i = 0;
    Uint32 pixel;
    Uint8 r, g, b;
    int coord;
    int y = 0;
    int x = 0;
    while(y < height)
    {
        while(x < width)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            while(x < width-1 && r == 0)
            {
                x++;
                pixel = get_pixel(image, x, y);
                SDL_GetRGB(pixel, image->format, &r, &g, &b);
            }
            if(r == 255)
            {
                pos[y] = 0;
                y++;
                x = 0;
            }
        }
    }
}

// newpos = array taille Y image - 1 la ou faut garder les coordonnees de lignes
void updateYpos(int pos[], int height, int width)
{
    int n;
    while(i < height-1)
    {
        if(pos[i] == 0) // i = coord du haut
        {
            n = i;
            while(n < height-1 && n == 0) // n = coord du bas
                n++;
           
        }
    }
}
