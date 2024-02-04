#include <stdio.h>
#include <string.h>

#include "grid_read.h"

/*
 * Function: grid_read
 * ----------------------------
 *   Reads a grid format file and returns a string of the grid
 *   ONLY WORKS WITH FILES IN THE RIGHT GRID FORMAT
 *
 *   arg: The FILE pointer of the grid
 *
 *   returns: A string containing the grid of the file
 */
const char* grid_read(FILE *fptr)
{
    
    static char res[111] =""; // static to maintain the variable out of the function
    char temp[13];
    for(int i = 0; i < 11; i++) // Reads the file line by line
    {
        strcat(res, fgets(temp, sizeof(temp), fptr));
    }
    return res;
}

const char* grid_read2(FILE *fptr)
{
    
    static char res[111] =""; // static to maintain the variable out of the function
    char temp[13];
    for(int i = 0; i < 11; i++) // Reads the file line by line
    {
        strcat(res, fgets(temp, sizeof(temp), fptr));
    }
    return res;
}
