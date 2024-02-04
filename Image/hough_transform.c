#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <math.h>
#include "hough_transform.h"
#include "pixel_operations.h"
#include "display.h"

#define pi 3.14159265359

double Convert(int degree)
{
	return degree * (pi / 180);
}
struct triple
{
	int height;
	int width;
	int length;
};

int* verticalLength(int* length,int i,int j,int height,SDL_Surface* surface)
{
	int* result = malloc(sizeof(int) *100000);
	for(int e = height - 1; e > j; e--)
	{
		Uint32 pixel = get_pixel(surface, i, e);
            	Uint8 r,g,b;
            	SDL_GetRGB(pixel, surface->format, &r, &g, &b);
		if(r == 178)
		{
			*(result + *length) = e - j;
			*length += 1;
		}

	}
	return result;
}


int* horizontalLength(int* length,int i,int j,int width,SDL_Surface* surface)
{	
	int* result = malloc(sizeof(int) * 100000);
	for(int e = width - 1; e > i; e--)
	{
		Uint32 pixel = get_pixel(surface, e, j);
            	Uint8 r,g,b;
            	SDL_GetRGB(pixel, surface->format, &r, &g, &b);
		if(r == 178)
		{
			*(result + *length) = e - i;
			*length += 1;
		}

	}
	return result;
}

int maxLength(int* verticalLengths, int* horizontalLengths, int vL,int hL)
{
	int e = 0;
	int e2 = 0;
	int maxlength = 0;
	while(e < vL)
	{
		while(e2 < hL)
		{
			if((*(verticalLengths+e))+10 >= *(horizontalLengths+e2) && (*(verticalLengths+e))-10 <= *(horizontalLengths+e2))
			{
				int vLength = *(verticalLengths+e);
				if(maxlength < vLength)
				{
					maxlength=(vLength);
				}
			}
			e2+=1;
		}
		e2 =0;
		e +=1;
	}
	return maxlength;
}

void squaredetect()
{
	SDL_Surface* surface = IMG_Load("../UI/intersection.bmp");
	int width = surface->w;
	int height = surface->h;
	struct triple sqrmax;
	sqrmax.height = 0;
	sqrmax.width = 0;
	sqrmax.length = 0;
	for(int i = 0; i < width/2; i++)
	{
		for(int j = 0 ; j < height/2;j++)
		{
			Uint32 pixel = get_pixel(surface, i, j);
            		Uint8 r,g,b;
            		SDL_GetRGB(pixel, surface->format, &r, &g, &b);
			if(r == 178)
			{
				int vL = 0;
				int hL= 0;
				int *verticalLengths = verticalLength(&vL,i,j,height,surface);
				int *horizontalLengths = horizontalLength(&hL,i,j,width,surface);
				int maxlength = maxLength(verticalLengths, horizontalLengths, vL,hL);
				if(maxlength != 0)
				{
					struct triple coord;
					coord.height = j;
					coord.width = i;
					coord.length = maxlength;
					if(coord.length > sqrmax.length)
					{
						sqrmax.height = coord.height;
						sqrmax.width = coord.width;
						sqrmax.length = coord.length;
						//printf("hL = %i\n,vL = %i\n",hL,vL);
					}
				}
				free(verticalLengths);
				free(horizontalLengths);
			}

		}
	}
	if(sqrmax.length != 0)
	{
		SDL_Surface* image = IMG_Load("intersection.bmp");
		SDL_Surface* imagedest = SDL_CreateRGBSurface(0,sqrmax.length,sqrmax.length,32,0,0,0,0);
		SDL_Rect leftR = {sqrmax.width,sqrmax.height, sqrmax.length, sqrmax.length};
		SDL_BlitSurface(image,&leftR,imagedest,NULL);
		SDL_SaveBMP(imagedest,"final_square.bmp");
		SDL_FreeSurface(imagedest);
		SDL_FreeSurface(image);

	}
	SDL_FreeSurface(surface);

}



const char *edge_detection(SDL_Surface* image)
{
    SDL_Surface *toRotate = loadImage("../Image/image_05.jpeg");
    if(image->w == toRotate->w && image->h == toRotate->h)
    {
        printf("wtf\n");
        return edge_detection2(image);
    }
    
 int width = image->w;
    int height = image->h;
    int diagonale = floor(sqrt((double) (width * width + height * height)));

    // there will be 180 teta since we go from 0 include to 180 excluded
    // there will be diagonale rho
    int A[diagonale][180];
    for (int i = 0; i < diagonale; i++)
    {
        for (int j = 0; j < 180; j++)
        {
            A[i][j] = 0;
        }
    }

    for (double x = 10; x < width-10; x++)
    {
        for (double y = 10; y < height-10; y++)
        {
            Uint32 pixel = get_pixel(image, floor(x), floor(y));
            Uint8 r,g,b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            if (r  > 120)
            {
                for (int teta = 0; teta < 180; teta++)
                {
                    double tetaRad = Convert(teta);
                    //printf("floor(cos) = %i  teta = %i\n", rho, teta);
                    //if (x * (cos(tetaRad)) - y * (sin(tetaRad) + x * cos(tetaRad) + y * sin(tetaRad)) == 0)
                    {
                        
                        int rho = abs((int) floor(x * cos(tetaRad) + y * sin(tetaRad)));
                        //printf("rho = %i\n", rho);
                        A[rho][teta] += 1;
                        //printf("long thing = %f cos(rho) = %i  cos(tetaRad) = %f  sin(tetaRad) = %f  x = %f  y = %f\n", x * (cos(tetaRad)) - y * (sin(tetaRad)) + rho, rho, cos(tetaRad), sin(tetaRad), x, y);
                        //printf("hello my bwuda 2\n");
                            /*for (int i = -1; i < 2; i++)
                            {
                                for (int j = -1; j < 2; j++)
                                {   
                                    if (rho + i >= 0 && rho + i < diagonale && teta + j >= 0 && teta + j < 180)
                                    {
                                        //printf("hello my bwuda 3\n");
                                        A[rho + i][teta + j] += 1;
                                    }
                                }
                            }*/
                    }
                }
            }
        }
    }

    
    // EDGE DETECTION DONE
    //

   /* int *tetas = calloc(180,sizeof(int));
    for (int i= 0; i< 180; i++)
    {
	    for (int j = 0; j < diagonale; j++)
	    {
		    if(A[j][i] > 250)
			    tetas[i]++;
	    }
    }
    int maxVertical = 45;
    int maxHorizontal = 0;
    for(int i = 0; i < 180; i++)
    {
	    if(i > 45 && i < 135)
	    {
		    if (tetas[maxVertical] < tetas[i])
			    maxVertical = i;
	    }
	    else
	    {
		    if(tetas[maxHorizontal] < tetas[i])
			    maxHorizontal = i;
	    }
    }
    printf("maxVertical = %i\n",maxVertical);
    printf("maxVertical = %i\n",maxHorizontal);
    */

    //image = rotozoomSurface(image,maxVertical - 90,1.0,2);
    /*
    for (int i = 0; i < diagonale; i++)
    {
        for (int j = 0; j < 180; j++)
        {
            A[i][j] = 0;
        }
    }

    for(double x = 10; x < width - 10; x++)
    {
	    for(double y = 10; y < height - 10; y++)
	    {
		    Uint32 pixel = get_pixel(image,floor(x),floor(y));
		    Uint8 r,g,b;
		    SDL_GetRGB(pixel,image->format,&r,&g,&b);
		    if ( r > 120 )
		    {
			    for( int teta = 0; teta < 180; teta++)
			    {
				    double tetaRad = Convert(teta);
				    {
					    int rho = abs((int) floor(x * cos(tetaRad) + y * sin(tetaRad)));
					     A[rho][teta] += 1;
				    }
			    }
		    }
	    }
    }
    */
 SDL_Surface* houghSpace = SDL_CreateRGBSurface(0, 180, diagonale, 32, 0, 0, 0, 0);
  SDL_Surface* intersection = loadImage("image.bmp");

    int Line =0;
    for (int j = 0; j < 180; j+=90)
    {
        for (int i = 0; i < diagonale-29; i+=30)
        {
	    	int indexk = 0;
		int imax = 0;
		int max = 0;
                for (int k =0 ; k <= 30; k++)
                {
                        if (i+k >= 0 && i+k < diagonale)
                        {
				if( A[i+k][j] >= max)
				{
                            		max = A[i+k][j];
                            		indexk = i+k;
					A[imax][k]=-1;
					imax = i+k;
				}
				else
				{
					A[i+k][j] = -1; 
				}
                        }
                }

            //printf("this : %i\n", A[i][j]);
            if (A[indexk][j] >500)
            {
                    /*for (int x = 0; x < width; x++)
                    {
                        printf("teta = %i\n", j);
                        if (j == 0)
                        {
                            int y = (int) (indexk - x * pi / 2);
                            
                            //printf("x = %i    y = %i\n", x, y);
                            Uint32 pix = SDL_MapRGB(image->format, 178, 34, 34);
                            if (y < 1000 && y >= 0)
                            {
                                put_pixel(image, x, y, pix);
                            }
                            else
                            {
                                //printf("y over 1000 : %i\n", y);
                            }
                        }
                        if (j == 90)
                        {
                            int y = (int) (indexk - x * cos(Convert(j)) / sin(Convert(j)));
                            //printf("x = %i    y = %i\n", x, y);
                            Uint32 pix = SDL_MapRGB(image->format, 178, 34, 34);
                            if (y < 1000 && y >= 0)
                            {
                                put_pixel(image, x, y, pix);
                            }
                            else
                            {
                                //printf("y over 1000 : %i\n", y);
                            }
                        }
                        
                    }*/
                    if (j >= 90 && j <= 90)
                    {
                        for (int x = 0; x < width; x++)
                        {
                            int y = (int) (indexk - x * cos(Convert(j)) / sin(Convert(j)));
                            //printf("x = %i    y = %i\n", x, y);
                            Uint32 pix = SDL_MapRGB(image->format, 178, 33, 33);
                            if (y < height && y >= 0)
                            {
				Uint32 pixel = get_pixel(image, floor(x), floor(y));
            			Uint8 r,g,b;
            			SDL_GetRGB(pixel, image->format, &r, &g, &b);

				if(r == 178)
				{
					put_pixel(intersection,x,y,pix);
				}

                                put_pixel(image, x, y, pix);
				Line +=1;

                            }
                            else
                            {
                                //printf("y over 1000 : %i\n", y);
                            }
                        }
                    }
                    if (j == 0)
                    {
                        for (int y = 0; y < height; y++)
                        {
                            int x = (int) (indexk - y * sin(Convert(j)) / cos(Convert(j)));
                            //printf("x = %i    y = %i\n", x, y);
                            Uint32 pix = SDL_MapRGB(image->format, 178, j, j);
                            if (x < width && x >= 0)
                            {
				Uint32 pixel = get_pixel(image, floor(x), floor(y));
            			Uint8 r,g,b;
            			SDL_GetRGB(pixel, image->format, &r, &g, &b);

				if(r == 178)
				{
					put_pixel(intersection,x,y,pix);
				}
                                put_pixel(image, x, y, pix);
				Line += 1;
                            }
                            else
                            {
                                //printf("y over 1000 : %i\n", y);
                            }
                        }
                    }
                //int x = i * floor(cos(j));
                //int y = i * floor(sin(j));
            }
        }
    }

	
   

    
    SDL_SaveBMP(houghSpace, "houghSpace.bmp");
    SDL_SaveBMP(image, "mmm.bmp");
    SDL_SaveBMP(intersection, "intersection.bmp");

    SDL_FreeSurface(intersection);
    SDL_FreeSurface(houghSpace);
    SDL_FreeSurface(image);

    return "mmm.bmp";
}



const char *edge_detection2(SDL_Surface* image)
{
    //SDL_Surface* image = IMG_Load(path);

    int width = image->w;
    int height = image->h;
    int diagonale = floor(sqrt((double) (width * width + height * height)));

    // there will be 180 teta since we go from 0 include to 180 excluded
    // there will be diagonale rho
    int A[diagonale][180];
    for (int i = 0; i < diagonale; i++)
    {
        for (int j = 0; j < 180; j++)
        {
            A[i][j] = 0;
        }
    }

    for (double x = 10; x < width-10; x++)
    {
        for (double y = 10; y < height-10; y++)
        {
            Uint32 pixel = get_pixel(image, floor(x), floor(y));
            Uint8 r,g,b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            if (r  > 120)
            {
                for (int teta = 0; teta < 180; teta++)
                {
                    double tetaRad = Convert(teta);
                    //printf("floor(cos) = %i  teta = %i\n", rho, teta);
                    //if (x * (cos(tetaRad)) - y * (sin(tetaRad) + x * cos(tetaRad) + y * sin(tetaRad)) == 0)
                    {
                        
                        int rho = abs((int) floor(x * cos(tetaRad) + y * sin(tetaRad)));
                        //printf("rho = %i\n", rho);
                        A[rho][teta] += 1;
                        //printf("long thing = %f cos(rho) = %i  cos(tetaRad) = %f  sin(tetaRad) = %f  x = %f  y = %f\n", x * (cos(tetaRad)) - y * (sin(tetaRad)) + rho, rho, cos(tetaRad), sin(tetaRad), x, y);
                        //printf("hello my bwuda 2\n");
                            /*for (int i = -1; i < 2; i++)
                            {
                                for (int j = -1; j < 2; j++)
                                {   
                                    if (rho + i >= 0 && rho + i < diagonale && teta + j >= 0 && teta + j < 180)
                                    {
                                        //printf("hello my bwuda 3\n");
                                        A[rho + i][teta + j] += 1;
                                    }
                                }
                            }*/
                    }
                }
            }
        }
    }

    
    // EDGE DETECTION DONE
    //

   int *tetas = calloc(180,sizeof(int));
    for (int i= 0; i< 180; i++)
    {
	    for (int j = 0; j < diagonale; j++)
	    {
		    if(A[j][i] > 250)
			    tetas[i]++;
	    }
    }
    int maxVertical = 45;
    int maxHorizontal = 0;
    for(int i = 0; i < 180; i++)
    {
	    if(i > 45 && i < 135)
	    {
		    if (tetas[maxVertical] < tetas[i])
			    maxVertical = i;
	    }
	    else
	    {
		    if(tetas[maxHorizontal] < tetas[i])
			    maxHorizontal = i;
	    }
    }
    printf("maxVertical = %i\n",maxVertical);
    printf("maxVertical = %i\n",maxHorizontal);
    

    image = rotozoomSurface(image,maxVertical - 90,1.0,2);
    
    for (int i = 0; i < diagonale; i++)
    {
        for (int j = 0; j < 180; j++)
        {
            A[i][j] = 0;
        }
    }

    for(double x = 10; x < width - 10; x++)
    {
	    for(double y = 10; y < height - 10; y++)
	    {
		    Uint32 pixel = get_pixel(image,floor(x),floor(y));
		    Uint8 r,g,b;
		    SDL_GetRGB(pixel,image->format,&r,&g,&b);
		    if ( r > 120 )
		    {
			    for( int teta = 0; teta < 180; teta++)
			    {
				    double tetaRad = Convert(teta);
				    {
					    int rho = abs((int) floor(x * cos(tetaRad) + y * sin(tetaRad)));
					     A[rho][teta] += 1;
				    }
			    }
		    }
	    }
    }

	

	
    SDL_Surface* houghSpace = SDL_CreateRGBSurface(0, 180, diagonale, 32, 0, 0, 0, 0);
    int threshold = 300;

    for (int i = 0; i < diagonale - 9; i+=10)
    {
        for (int j = 0; j < 180; j++)
        {
            int indexk = 0;
            int max = 0;
            for (int k = 0; k < 10; k++)
                {
                    //for (int l = -2; l < 3; l++)
                    {
                        
                        if (i+k >= 0 && i+k < diagonale && A[i+k][j] > max)
                        {
                            
                            max = A[i+k][j];
                            indexk = i+k;
                            
                        }
                    }
                }

            threshold = 300;
	    if (abs(maxVertical - 90) > 4)
	    {
		    threshold = 200;
	    }
            
            if (A[indexk][j] > threshold)
            {
                int value = A[i][j];
                value = (255 * value) / 1;
                //printf("value = %i\n", value);

                Uint32 pixel = SDL_MapRGB(houghSpace->format, (Uint8) value, (Uint8) value, (Uint8) value);
                put_pixel(houghSpace, j, i, pixel);

                
                

                    /*for (int x = 0; x < width; x++)
                    {
                        printf("teta = %i\n", j);
                        if (j == 0)
                        {
                            int y = (int) (indexk - x * pi / 2);
                            
                            //printf("x = %i    y = %i\n", x, y);
                            Uint32 pix = SDL_MapRGB(image->format, 178, 34, 34);
                            if (y < 1000 && y >= 0)
                            {
                                put_pixel(image, x, y, pix);
                            }
                            else
                            {
                                //printf("y over 1000 : %i\n", y);
                            }
                        }
                        if (j == 90)
                        {
                            int y = (int) (indexk - x * cos(Convert(j)) / sin(Convert(j)));
                            //printf("x = %i    y = %i\n", x, y);
                            Uint32 pix = SDL_MapRGB(image->format, 178, 34, 34);
                            if (y < 1000 && y >= 0)
                            {
                                put_pixel(image, x, y, pix);
                            }
                            else
                            {
                                //printf("y over 1000 : %i\n", y);
                            }
                        }
                        
                    }*/
                    if (j == 90)
                    {
                        for (int x = 0; x < width; x++)
                        {
                            int y = (int) (indexk - x * cos(Convert(j)) / sin(Convert(j)));
                            //printf("x = %i    y = %i\n", x, y);
                            Uint32 pix = SDL_MapRGB(image->format, 178, 34, 34);
                            if (y < height && y >= 0)
                            {
                                put_pixel(image, x, y, pix);
                            }
                            else
                            {
                                //printf("y over 1000 : %i\n", y);
                            }
                        }
                    }
                    if (j == 0)
                    {
                        for (int y = 0; y < height; y++)
                        {
                            int x = (int) (indexk - y * sin(Convert(j)) / cos(Convert(j)));
                            //printf("x = %i    y = %i\n", x, y);
                            Uint32 pix = SDL_MapRGB(image->format, 178, 34, 34);
                            if (x < width && x >= 0)
                            {
                                put_pixel(image, x, y, pix);
                            }
                            else
                            {
                                //printf("y over 1000 : %i\n", y);
                            }
                        }
                    }
                        
                        
                
                //int x = i * floor(cos(j));
                //int y = i * floor(sin(j));
            }
        }
    }

    printf("%i\n", threshold);
    const char *ppp = "muchachos.bmp";
    SDL_SaveBMP(houghSpace, ppp);
    SDL_SaveBMP(image, "muchachos.bmp");

    SDL_FreeSurface(houghSpace);
    SDL_FreeSurface(image);
    
    return ppp;
}
