#ifndef HOUGH_H
#define HOUGH_H

#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>

double to_radian(int degree);
void houghTransform(SDL_Surface* image, int accumulator[][181]);
void coordinates(int accumulator[][181], int rows, int cols);
void DrawLines(SDL_Surface* image);
void HoughMain(SDL_Surface* image);

#endif
