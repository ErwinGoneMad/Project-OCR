#ifndef REMOVE_COLOR_H_
#define REMOVE_COLOR_H_

#include <stdlib.h>
#include "pixel_operations.h"
#include <SDL/SDL.h>

SDL_Surface* grayscale(SDL_Surface *image);
SDL_Surface* blackWhite(SDL_Surface *image);

#endif
