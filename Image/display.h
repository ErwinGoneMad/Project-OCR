#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdlib.h>
#include <SDL/SDL.h>

SDL_Surface *loadImage(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();

#endif
