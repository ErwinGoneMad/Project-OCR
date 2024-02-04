#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "grid_read.h"
#include "grid_write.h"
#include "sudoku_solver.h"

// The solver program
int main(int argc, const char * argv[])
{
    // Error: if there is more than one argument
    if (argc != 2)
        errx(1,"Error: ENTER ONE ARGUMENT ONLY");
    
    const char *path = argv[1];
    FILE *fptr;
    //opening the file for reading
    if ((fptr = fopen(path,"r")) == NULL)
        errx(1,"Error: The file \"%s\" does not exist",path);
    
    const char *res = grid_read(fptr);
    fclose(fptr);
    
    
    // Solving the Sudoku
    initialise_grid(res);
    solve();
    const char *solve = grid_to_string();
    if(str_is_equal(res,solve))
        err(1, "Error: THE ENTERED GRID IS NOT SOLVABLE");
    else
    {
        printf("SOLVED GRID BELOW:-------------------------------------------------- \n\n");
        print();
        printf("--------------------------------------------------------------------\n");
        printf("Storing the grid in a file------------------------------------------\n\n");
        
    }
    // store it in a file
    grid_write(solve,path);
    
    return 0;
}
