#include <stdio.h>
#include <string.h>
#include <err.h>

#include "grid_write.h"

/*
 * Function: grid_Write
 * ----------------------------
 *   Take in a string containing the grid and saves it in a file in grid format
 *
 *    arg: The string containing the grid
 *
 *   returns: No return
 */
void grid_write(const char* str, const char *path)
{
    FILE *fptr = fopen(strcat((char*)path,".result"),"w");
    
    if(fptr == NULL)
    {
        errx(1, "ERROR: The file was not created");
    }
    
    fprintf(fptr,"%s", str);
    fclose(fptr);
}
