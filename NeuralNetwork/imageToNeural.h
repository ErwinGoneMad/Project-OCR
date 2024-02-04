#ifndef IMAGETONEURAL_H_
#define IMAGETONEURAL_H_
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"


#define SIZE 784

SDL_Surface *loadImage(char *path);
void imageToNeural(SDL_Surface *img, float array[SIZE]);
#endif
