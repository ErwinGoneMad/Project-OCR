#include <err.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Solver/grid_read.h"
#include "display.h"
#include "reconstruct.h"

const int row1 = 14;
const int row2 = 61;
const int row3 = 106;
const int row4 = 155;
const int row5 = 201;
const int row6 = 247;
const int row7 = 296;
const int row8 = 342;
const int row9 = 388;
const int col1 = 14;
const int col2 = 62;
const int col3 = 110;
const int col4 = 161;
const int col5 = 209;
const int col6 = 257;
const int col7 = 309;
const int col8 = 355;
const int col9 = 406;
const int size_grid = 430;
const int size_img = 42;

void recon(const char *given, const char *res, SDL_Surface *grid)
{
    int col = col1;
    int row = row1;
    int i = 0;
    SDL_Surface *number = NULL;
    SDL_Rect rect_grid;
    while(*(res+i) != 0)
    {
        if(*(res+i) == '\n')
        {
            if(*(res+i+1) == '\n')
                i++;
            switch(row)
            {
            case row1:
                row = row2;
                break;
            case row2:
                row = row3;
                break;
            case row3:
                row = row4;
                break;
            case row4:
                row = row5;
                break;
            case row5:
                row = row6;
                break;
            case row6:
                row = row7;
                break;
            case row7:
                row = row8;
                break;
            case row8:
                row = row9;
                break;
            default:
                row = row9;
                break;
            }
            col = col1;
        }
        else if(*(res+i) != ' ')
        {
            switch(*(res+i))
            {
            case '1':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/1r.jpg");
                else
                    number = loadImage("Reco_images/1.png");
                break;
            case '2':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/2r.jpg");
                else
                    number = loadImage("Reco_images/2.png");
                break;
            case '3':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/3r.jpg");
                else
                    number = loadImage("Reco_images/3.png");
                break;
            case '4':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/4r.jpg");
                else
                    number = loadImage("Reco_images/4.png");
                break;
            case '5':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/5r.jpg");
                else
                    number = loadImage("Reco_images/5.png");
                break;
            case '6':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/6r.jpg");
                else
                    number = loadImage("Reco_images/6.png");
                break;
            case '7':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/7r.jpg");
                else
                    number = loadImage("Reco_images/7.png");
                break;
            case '8':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/8r.jpg");
                else
                    number = loadImage("Reco_images/8.png");
                break;
            case '9':
                if(*(given+i) == '.')
                    number = loadImage("Reco_images/9r.jpg");
                else
                    number = loadImage("Reco_images/9.png");
                break;
            }
            rect_grid.x = col;
            rect_grid.y = row;
            SDL_BlitSurface(number, NULL, grid, &rect_grid);
            switch(col)
            {
            case col1:
                col = col2;
                break;
            case col2:
                col = col3;
                break;
            case col3:
                col = col4;
                break;
            case col4:
                col = col5;
                break;
            case col5:
                col = col6;
                break;
            case col6:
                col = col7;
                break;
            case col7:
                col = col8;
                break;
            case col8:
                col = col9;
                break;
            default:
                col = col9;
                break;
            }
        }
        i++;
    }
    SDL_FreeSurface(number);
}

const char *file_image(char *path1, char *path2)
{
    FILE *fptr1;
    if ((fptr1 = fopen(path1,"r")) == NULL)
         errx(1,"Error: The file \"%s\" does not exist",path1);
    const char *given = grid_read(fptr1);
    fclose(fptr1);
    SDL_Surface *grid = loadImage("Reco_images/emptygrid.png");
    FILE *fptr2;
    if ((fptr2 = fopen(path2,"r")) == NULL)
        errx(1,"Error: The file \"%s\" does not exist",path2);
    // res = string avec \n retournant resultat
    const char *res = grid_read2(fptr2);
    fclose(fptr2);
    recon(given, res, grid);
    char *path3 = "result_image.bmp";
    if(SDL_SaveBMP(grid, path3) != 0)
    {
        // Error saving bitmap
        printf("SDL_SaveBMP failed: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(grid);
    return path3;
}
/*
int main()
{
    char *path1 = "given";
    char *path2 = "res";
    const char *result = file_image(path1, path2);
    printf("%s\n", result);
}
*/
