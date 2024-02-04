#ifndef GAUSSIAN_FILTER_H
#define GAUSSIAN_FILTER_H

#include <stdlib.h>
#include <SDL/SDL.h>

void updateKernel();
int updatePixel(Uint8 image[]);
void filter(SDL_Surface* image, SDL_Surface* n_image);

#endif
